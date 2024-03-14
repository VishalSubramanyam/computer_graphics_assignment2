/**
* Name: Vishal Subramanyam
 * Roll Number: 20CS10081
 * Email addr: vishalsubramanyam02@gmail.com
*/

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "generate_landscape.h"

#include <iostream>
#include <random>


/**
 * 1. Divide plane into squares
 * 2. For each square, with a probability inversely proportional to distance from origin, decide
 *    if the square should have a building.
 * 3. Height of the building is floored and ceiled based on distance from origin
 */
std::vector<Building> generate_landscape(std::int64_t l) {
    std::cout << "Was here" << std::endl;
    constexpr double HEIGHT_SCALE = 10.0;

    std::vector<Building> landscape;
    l = 2 * (l / 2) + 1;

    // set up probability distribution
    std::random_device rd{}; // use to seed the rng
    std::mt19937 rng{rd()}; // rng
    auto colorDist = std::uniform_real_distribution<float>(0.0f,1.0f); // distribution for random color
    for (int64_t x = -(l / 2); x <= (l / 2); x++) {
        for (int64_t y = -(l / 2); y <= (l / 2); y++) {
            uint64_t distance = std::sqrt(x * x + y * y);
            auto distInverse = 1.0 / static_cast<double>(distance + 1); // 1 / (d + 1)
            auto heightFunc = distInverse;
            double heightFloor = 1 + HEIGHT_SCALE * heightFunc; // min height possible for a building
            double heightCeiling = 1.3 * heightFloor; // max height for a building
            auto probability = std::min(0.94, 2 * distInverse); // prob that a building is made here
            bool placeBuilding = std::bernoulli_distribution(probability)(rng); // 0-1 choice based on rng
            if (placeBuilding)
                landscape.push_back(Building{
                    x, y, std::uniform_real_distribution<double>(heightFloor, heightCeiling)(rng), {colorDist(rng), colorDist(rng), colorDist(rng)}
                });
        }
    }
    return landscape;
}

void drawCuboid(float x, float y, float z, float height, float const color[]) {
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    constexpr float length = 1, width = 1;
    // Push the current matrix onto the stack
    glPushMatrix();

    // Set color to random color
    glColor3fv(color);

    // Translate to the specified position with the base on y = 0 plane
    glTranslatef(x, y, z); // Adjust for the center of the cuboid

    // Draw the cuboid
    glBegin(GL_QUADS);

    // Bottom face
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-length / 2, 0.0f, -width / 2);
    glVertex3f(length / 2, 0.0f, -width / 2);
    glVertex3f(length / 2, 0.0f, width / 2);
    glVertex3f(-length / 2, 0.0f, width / 2);

    // Top face
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-length / 2, height, -width / 2);
    glVertex3f(length / 2, height, -width / 2);
    glVertex3f(length / 2, height, width / 2);
    glVertex3f(-length / 2, height, width / 2);

    // Front face
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-length / 2, 0.0f, -width / 2);
    glVertex3f(length / 2, 0.0f, -width / 2);
    glVertex3f(length / 2, height, -width / 2);
    glVertex3f(-length / 2, height, -width / 2);

    // Back face
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-length / 2, 0.0f, width / 2);
    glVertex3f(length / 2, 0.0f, width / 2);
    glVertex3f(length / 2, height, width / 2);
    glVertex3f(-length / 2, height, width / 2);

    // Left face
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-length / 2, 0.0f, -width / 2);
    glVertex3f(-length / 2, 0.0f, width / 2);
    glVertex3f(-length / 2, height, width / 2);
    glVertex3f(-length / 2, height, -width / 2);

    // Right face
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(length / 2, 0.0f, -width / 2);
    glVertex3f(length / 2, 0.0f, width / 2);
    glVertex3f(length / 2, height, width / 2);
    glVertex3f(length / 2, height, -width / 2);

    glEnd();

    // Restore the previous matrix from the stack
    glPopMatrix();
}