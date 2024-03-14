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

constexpr uint64_t mapLength = 50;

// Global variables to store the accumulated rotation angle based on mouse movement
float rotateMouseX = 0.0f;
float rotateMouseY = 0.0f;
int prevMouseX = 0;
int prevMouseY = 0;
float fbDistance = 0;

auto buildings = generate_landscape(mapLength);

void display() {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    auto const &l = mapLength;

    // create a plane
    int const CORNER = static_cast<int>((l + 3) / 2);
    int TOP_LEFT[] = {-CORNER, 0, CORNER};
    int TOP_RIGHT[] = {CORNER, 0, CORNER};
    int BOTTOM_LEFT[] = {-CORNER, 0, -CORNER};
    int BOTTOM_RIGHT[] = {CORNER, 0, -CORNER};
    constexpr GLdouble const PLANE_COLOR[] = {0.5, 0.5, 0.5};


    setupLighting();
    glTranslatef(0, 0, fbDistance);

    gluLookAt(-CORNER - 10, CORNER, CORNER + 10, 0, 0, 0, 0, 1, 0);
    // Apply accumulated mouse rotation angles
    glRotatef(rotateMouseX, 1.0f, 0.0f, 0.0f); // apply mouse rotation about x axis
    glRotatef(rotateMouseY, 0.0f, 1.0f, 0.0f); // apply mouse rotation about y axis
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glBegin(GL_QUADS);
    glColor3dv(PLANE_COLOR);
    glNormal3f(0.0f, 1.0f, 0.0f); // need to define the normal vector for this plane, so that lighting works
    glVertex3iv(TOP_LEFT);
    glVertex3iv(TOP_RIGHT);
    glVertex3iv(BOTTOM_RIGHT);
    glVertex3iv(BOTTOM_LEFT);
    glEnd();
    for(auto const &building : buildings) {
        drawCuboid(building.x, 0, building.z, building.height);
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
    buildings = generate_landscape(mapLength);
    glutMainLoop();
    return 0;
}
