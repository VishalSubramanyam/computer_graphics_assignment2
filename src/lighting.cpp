/**
* Name: Vishal Subramanyam
 * Roll Number: 20CS10081
 * Email addr: vishalsubramanyam02@gmail.com
*/

// Code for managing lighting

#include "lighting.h"
#include <GL/glut.h>

// Light properties - can modify as needed
constexpr GLfloat ambient[] = {1, 1, 1, 1.0f};
constexpr GLfloat diffuse[] = {1, 1, 1, 1.0f};
constexpr GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
constexpr GLfloat shininess[] = {50.0f};
constexpr GLfloat lightPosition[] = {2000.0f, 2000.0f, 2000.0f, 1.0f};

void setupLighting() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING); // Enable lighting
    glEnable(GL_LIGHT0); // Enable light source 0
    glEnable(GL_COLOR_MATERIAL); // Enable coloring of materials
    glShadeModel(GL_SMOOTH); // smooth shading
    // Set light position
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    // set lighting properties for materials
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}
