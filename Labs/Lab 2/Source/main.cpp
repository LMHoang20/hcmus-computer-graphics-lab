#include <GL/glut.h>
#include <iostream>
#include "application.h"
#include "constants.h"
#include "button.h"
using namespace std;

App* app = nullptr;
Button* leftButton = nullptr;
Button* rightButton = nullptr;
Button* redrawButton = nullptr;
Button* checkButton = nullptr;

void drawEverything() {
	app->clearWindows();
	glColor3ub(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2i(0, HEIGHT);
	glVertex2i(WIDTH, HEIGHT);
	glEnd();
	leftButton->draw();
	rightButton->draw();
	redrawButton->draw();
	checkButton->draw();
	app->drawCurrentShape();
}

void display() {
	cout << "Windows changed, redraw shapes...\n";
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(2.0);
	drawEverything();
	glFlush();
}

void mouseClickHandler(int button, int state, int x, int y) {
	y = WINDOW_HEIGHT - y;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (leftButton->collision(x, y)) {
			if (!app->leftImage()) return;
			drawEverything();
		}
		else if (rightButton->collision(x, y)) {
			if (!app->rightImage()) return;
			drawEverything();
		}
		else if (redrawButton->collision(x, y)) {
			drawEverything();
		}
		else if (checkButton->collision(x, y)) {
			app->checkCurrentShape();
		}
	}
}

void keyPressHandler(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		if (!app->leftImage()) return;
		drawEverything();
		break;
	case 'd':
		if (!app->rightImage()) return;
		drawEverything();
		break;
	case 'r':
		drawEverything();
		break;
	case 'w':
		app->checkCurrentShape();
		break;
	default:
		return;
	}
}

void specialPressHandler(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		if (!app->leftImage()) return;
		drawEverything();
		break;
	case GLUT_KEY_RIGHT:
		if (!app->rightImage()) return;
		drawEverything();
		break;
	case GLUT_KEY_UP:
		app->checkCurrentShape();
		break;
	default:
		return;
	}
	
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Computer Graphics Lab 02");
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
	leftButton = new Button(25, WINDOW_HEIGHT - BUTTON_HEIGHT - 1, BUTTON_WIDTH + 25, WINDOW_HEIGHT - 1, "Previous(A)");
	rightButton = new Button(BUTTON_WIDTH + 50, WINDOW_HEIGHT - BUTTON_HEIGHT - 1, 2 * BUTTON_WIDTH + 50, WINDOW_HEIGHT - 1, "Next(D)");
	redrawButton = new Button(2 * BUTTON_WIDTH + 75, WINDOW_HEIGHT - BUTTON_HEIGHT - 1, 3 * BUTTON_WIDTH + 75, WINDOW_HEIGHT - 1, "Redraw(R)");
	checkButton = new Button(3 * BUTTON_WIDTH + 100, WINDOW_HEIGHT - BUTTON_HEIGHT - 1, 4 * BUTTON_WIDTH + 100, WINDOW_HEIGHT - 1, "Check(W)");
	app = new App(WIDTH, HEIGHT, INPUT_FILE); 
	glutDisplayFunc(display);
	glutMouseFunc(mouseClickHandler);
	glutKeyboardFunc(keyPressHandler);
	glutSpecialFunc(specialPressHandler);
	glutMainLoop();
	delete app;
	delete leftButton;
	delete rightButton;
	delete redrawButton;
	delete checkButton;
	cout << "Exit.";
	return 0;
}
