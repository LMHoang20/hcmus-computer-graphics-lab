/*
* OGL02Animation.cpp: 3D Shapes with animation
*/
#define _USE_MATH_DEFINES
#include <windows.h> // for MS Windows
#include <GL/glut.h> // GLUT, include glu.h and gl.h
#include <math.h>
#include <iostream>
#include "shape.h"

/* Global variables */
char title[] = "3D Shapes with animation";
std::vector < Shape* > shapes;
int refreshMills = 15; // refresh interval in milliseconds [NEW]
int degreeLR = 0;
int degreeUD = 30;
float camDistance = 10;

/* Initialize OpenGL Graphics */
void initGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClearDepth(1.0f); // Set background depth to farthest
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST); // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL); // Set the type of depth-test
	glShadeModel(GL_SMOOTH); // Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Nice perspective corrections
}
/* Handler for window-repaint event. Called back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
	glMatrixMode(GL_MODELVIEW); // To operate on model-view matrix
	for (auto& shape : shapes) {
		shape->draw();
		shape->rotate(1);
	}
	glutSwapBuffers(); // Swap the front and back frame buffers (double buffering)
	// Update the rotational angle after each refresh [NEW]
	
}
/* Called back when timer expired [NEW] */
void timer(int value) {
	glutPostRedisplay(); // Post re-paint request to activate display()
	glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}

GLsizei curWidth = 640, curHeight = 480;
void setupCamera() {
	float radianUD = degreeUD * M_PI / 180;
	float radianLR = degreeLR * M_PI / 180;
	float r = camDistance * cos(radianUD);
	float x = r * sin(radianLR);
	float y = -r * cos(radianLR);
	float z = camDistance * sin(radianUD);
	float upZ = 1;
	if (90 <= degreeUD && degreeUD < 270) {
		upZ = -1;
	}
	GLfloat aspect = (GLfloat)curWidth / (GLfloat)curHeight;
	glMatrixMode(GL_PROJECTION); // To operate on the Projection matrix
	glLoadIdentity(); // Reset
	// Enable perspective projection with fovy, aspect, zNear and zFar
	gluPerspective(60.0f, aspect, 0.1f, 100.0f);
	gluLookAt(x, y, z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, upZ);
}
/* Handler for window re-size event. Called back when the window first appears and
 whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) { // GLsizei for non-negative integer
	// Compute aspect ratio of the new window
	if (height == 0) height = 1; // To prevent divide by 0
	curWidth = width;
	curHeight = height;
	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);
	setupCamera();
}

void handleKeyboard(unsigned char key, int x, int y) {
	if (key == 'q') {
		camDistance -= 0.1f;
	}
	else if (key == 'e') {
		camDistance += 0.1f;
	}
	else if (key == 's') {
		(degreeUD += 359) %= 360;
	}
	else if (key == 'w') {
		(degreeUD += 1) %= 360;
	}
	else if (key == 'a') {
		(degreeLR += 359) %= 360;
	}
	else if (key == 'd') {
		(degreeLR += 1) %= 360;
	}
	else {
		return;
	}
	setupCamera();
	glutPostRedisplay();
}

void handleSpecial(int key, int x, int y) {
	if (key == GLUT_KEY_DOWN) {
		(degreeUD += 359) %= 360;
	}
	else if (key == GLUT_KEY_UP) {
		(degreeUD += 1) %= 360;
	}
	else if (key == GLUT_KEY_LEFT) {
		(degreeLR += 359) %= 360;
	}
	else if (key == GLUT_KEY_RIGHT) {
		(degreeLR += 1) %= 360;
	}
	else {
		return;
	}
	setupCamera();
	glutPostRedisplay();	
}
/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
	glutInit(&argc, argv); // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
	glutInitWindowSize(curWidth, curHeight); // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
	glutCreateWindow(title); // Create window with the given title
	glutDisplayFunc(display); // Register callback handler for window re-paint event
	glutSpecialFunc(handleSpecial);
	glutKeyboardFunc(handleKeyboard);
	glutReshapeFunc(reshape); // Register callback handler for window re-size event
	initGL(); // Our own OpenGL initialization
	glutTimerFunc(0, timer, 0); // First timer call immediately [NEW]
	shapes.push_back(new Cube       (-6.0f, +3.0f, 0.0f, 1.00f));
	shapes.push_back(new Sphere     (-2.0f, +3.0f, 0.0f, 1.00f, 50, 50));
	shapes.push_back(new Cylinder   (+2.0f, +3.0f, 0.0f, 1.00f, 2.00f, 50));
	shapes.push_back(new Cone       (+6.0f, +3.0f, 0.0f, 1.00f, 2.00f, 50, 50));
	shapes.push_back(new Torus      (-4.0f, -3.0f, 0.0f, 0.75f, 0.25f, 50, 50));
	shapes.push_back(new Hyperboloid(-0.0f, -3.0f, 0.0f, 0.50f, 0.30f, 1.0f, 50, 50));
	shapes.push_back(new Paraboloid (+4.0f, -3.0f, 0.0f, 1.00f, 1.0f, 50, 50));
	
	glutMainLoop(); // Enter the infinite event-processing loop
	return 0;
}
