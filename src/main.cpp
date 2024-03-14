/**
 * Name: Vishal Subramanyam
 * Roll Number: 20CS10081
 * Email addr: vishalsubramanyam02@gmail.com
*/
#include <iostream>
#include <GL/glut.h>

#include "generate_landscape.h"
#include "lighting.h"
#include "input_handlers.h"

constexpr int64_t mapLength = 50;

// Global variables to store the accumulated rotation angle based on mouse movement
float rotateMouseX = 0.0f;
float rotateMouseY = 0.0f;
int prevMouseX = 0;
int prevMouseY = 0;
float fbDistance = 0;

// generates the required buildings, buildings = vector<Building> (refer generate_landscape.h/cpp)
auto buildings = generate_landscape(mapLength);

void display() {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    auto const &l = mapLength;

    // create a plane
    int const CORNER = static_cast<int>((l + 3) / 2);

    setupLighting();


    double eye_x, eye_y, eye_z;
    eye_x = -CORNER - 10;
    eye_y = CORNER;
    eye_z = CORNER+10;
    glTranslatef(0, 0, fbDistance);
    // place the camera at a certain CORNER
    glRotatef(rotateMouseX, 1.0f, 0.0f, 0.0f); // apply mouse rotation about x axis
    glRotatef(rotateMouseY, 0.0f, 1.0f, 0.0f); // apply mouse rotation about y axis
    gluLookAt(eye_x, eye_y, eye_z, 0, 0, 0, 0, 1, 0);
    // Apply accumulated mouse rotation angles
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    // for every possible building, draw a cuboid at the building's coordinates

    for(auto const &building : buildings) {
        drawCuboid(building.x, 0, building.z, building.height, building.color);
    }

    glutSwapBuffers();
}

void idle() {
    glutPostRedisplay();
}

void reshape(int w, int h) {
    // Set the viewport to cover the entire window
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);

    // Set the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat) w / (GLfloat) h, 0.1, 100.0);

    // Switch back to modelview matrix for transformations
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Assignment 2");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    glutMouseFunc(mouse); // detecting mouse clicks
    glutMotionFunc(mouseMotion); // for dragging the mouse with left button
    glutKeyboardFunc(keyboard_handler); // handles ASCII keycodes
    glutMainLoop();
    return 0;
}
