/**
* Name: Vishal Subramanyam
 * Roll Number: 20CS10081
 * Email addr: vishalsubramanyam02@gmail.com
*/

#include "input_handlers.h"
#include <iostream>
#include <GL/glut.h>
extern float rotateMouseX;
extern float rotateMouseY;
extern int prevMouseX;
extern int prevMouseY;
extern float fbDistance;


constexpr char const *INVALID_KEY_MSG = "Invalid keypress. Valid keys are F and B.";

void keyboard_handler(unsigned char key, int x, int y) {
    if (key == 'f' || key == 'F') {
        fbDistance += 0.5;
    } else if (key == 'b' || key == 'B') {
        fbDistance -= 0.5;
    } else {
        std::cerr << INVALID_KEY_MSG << std::endl;
    }
}


// Function to handle mouse motion
void mouseMotion(int x, int y) {
    // Calculate the change in mouse position
    int deltaX = x - prevMouseX;
    int deltaY = y - prevMouseY;

    // Update the accumulated rotation angles based on mouse movement
    rotateMouseY += 0.2 * deltaX;
    rotateMouseX += 0.2 * deltaY;

    // Remember the current mouse position for the next callback
    prevMouseX = x;
    prevMouseY = y;

    glutPostRedisplay(); // Trigger redraw to update the scene
}

// Function to handle mouse button press
void mouse(int button, int state, int x, int y) {
    // Store the current mouse position when a button is pressed
    if (state == GLUT_DOWN) {
        prevMouseX = x;
        prevMouseY = y;
    }
}
