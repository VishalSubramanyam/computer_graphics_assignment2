#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "generate_landscape.h"

#include <random>


/**
 * 1. Divide plane into squares
 * 2. For each square, with a probability inversely proportional to distance from origin, decide
 *    if the square should have a building.
 * 3. Height of the building is floored and ceiled based on distance from origin
 */
std::vector<Building> generate_landscape(std::size_t l) {
    constexpr double HEIGHT_SCALE = 2.0;

    std::vector<Building> landscape;
    l = 2 * (l / 2) + 1;

    // set up probability distribution
    std::random_device rd{}; // use to seed the rng
    std::mt19937 rng{rd()}; // rng
    for (int64_t x = -(l / 2); x <= (l / 2); x++) {
        for (int64_t y = -(l / 2); y <= (l / 2); y++) {
            uint64_t distance = std::sqrt(x * x + y * y);
            auto distInverse = 1.0 / static_cast<double>(distance + 1);
            double heightFloor = HEIGHT_SCALE * distInverse;
            double heightCeiling = 2 * HEIGHT_SCALE * distInverse;
            auto probability = std::min(1.0, 10 * distInverse);
            bool placeBuilding = std::bernoulli_distribution(probability)(rng);
            if (placeBuilding)
                landscape.push_back(Building{
                    x, y, std::uniform_real_distribution<double>(heightFloor, heightCeiling)(rng)
                });
        }
    }
    return landscape;
}

void drawCuboid(float x, float y, float z, float height) {
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    constexpr float length = 1, width = 1;
    // Push the current matrix onto the stack
    glPushMatrix();

    // Set color to random color
    glColor3f(dist(rng), dist(rng), dist(rng));

    // Translate to the specified position
    glTranslatef(x, y, z);

    // Draw the cuboid
    glBegin(GL_QUADS);

    // Bottom face
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-length / 2, -width / 2, 0.0f);
    glVertex3f(length / 2, -width / 2, 0.0f);
    glVertex3f(length / 2, width / 2, 0.0f);
    glVertex3f(-length / 2, width / 2, 0.0f);

    // Top face
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-length / 2, -width / 2, height);
    glVertex3f(length / 2, -width / 2, height);
    glVertex3f(length / 2, width / 2, height);
    glVertex3f(-length / 2, width / 2, height);

    // Front face
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-length / 2, -width / 2, 0.0f);
    glVertex3f(length / 2, -width / 2, 0.0f);
    glVertex3f(length / 2, -width / 2, height);
    glVertex3f(-length / 2, -width / 2, height);

    // Back face
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-length / 2, width / 2, 0.0f);
    glVertex3f(length / 2, width / 2, 0.0f);
    glVertex3f(length / 2, width / 2, height);
    glVertex3f(-length / 2, width / 2, height);

    // Left face
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-length / 2, -width / 2, 0.0f);
    glVertex3f(-length / 2, width / 2, 0.0f);
    glVertex3f(-length / 2, width / 2, height);
    glVertex3f(-length / 2, -width / 2, height);

    // Right face
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(length / 2, -width / 2, 0.0f);
    glVertex3f(length / 2, width / 2, 0.0f);
    glVertex3f(length / 2, width / 2, height);
    glVertex3f(length / 2, -width / 2, height);

    glEnd();

    // Restore the previous matrix from the stack
    glPopMatrix();
}