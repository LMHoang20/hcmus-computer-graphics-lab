#include <GL/glut.h>
#include <iostream>
#include <set>
#include <queue>
#include "application.h"
#include "constants.h"
#include "button.h"
#include "polygon.h"
using namespace std;

static int window;
static int value = 0;

const auto WHITE = RGBColor(255, 255, 255);
const auto BLACK = RGBColor(0, 0, 0);
const auto BLUE = RGBColor(0, 0, 255);
const auto RED = RGBColor(255, 0, 0);
const auto YELLOW = RGBColor(255, 255, 0);
const auto BLUE_TMP = RGBColor(0, 0, 254);
const auto RED_TMP = RGBColor(254, 0, 0);
const auto YELLOW_TMP = RGBColor(254, 254, 0);

const auto CENTER = Point(WIDTH / 2, HEIGHT / 2);
const vector < Point > directions = { Point(0, 1), Point(1, 0), Point(0, -1), Point(-1, 0) };

Point current_position = CENTER;
RGBColor current_color = BLUE;
RGBColor current_color_tmp = BLUE_TMP;
bool clear = true;

void menu(int num) {
	value = num;
	if (value == 16) current_color = BLUE, current_color_tmp = BLUE_TMP;
	else if (value == 17) current_color = RED, current_color_tmp = RED_TMP;
	else if (value == 18) current_color = YELLOW, current_color_tmp = YELLOW_TMP;
	else if (value == 19) clear = true;
	glutPostRedisplay();
}

int createSubmenuEntries(vector < const char* > labels, int start_index) {
	int submenu_id = glutCreateMenu(menu);
	for (int i = 0; i < labels.size(); ++i) {
		glutAddMenuEntry(labels[i], start_index + i);
	}
	return submenu_id;
}

void createMenu(void) {
	vector < int > submenu_ids;
	vector < vector < const char* > > submenu_labels = {
		{ "Vuong can", "Deu" },
		{ "Hinh chu nhat", "Hinh vuong" },
		{ "Hinh tron", "Elip" },
		{ "Ngu giac deu", "Luc giac deu" },
		{ "Mui ten", "Ngoi sao" },
		{ "Cong", "Tru", "Nhan", "Chia" },
		{ "Xanh", "Do", "Vang" }
	};
	vector < const char* > menu_labels = {
		"Tam giac", "Tu giac", "Oval", "Da giac deu", "Hinh khac", "Dau", "To mau"
	};
	for (int i = 0, start_id = 2; i < menu_labels.size(); ++i) {
		submenu_ids.push_back(createSubmenuEntries(submenu_labels[i], start_id));
		start_id += submenu_labels[i].size();
	}
	int menu_id = glutCreateMenu(menu);
	glutAddMenuEntry("Duong thang", 1);
	for (int i = 0; i < menu_labels.size(); ++i) {
		glutAddSubMenu(menu_labels[i], submenu_ids[i]);
	}
	glutAddMenuEntry("Xoa hinh", 19);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void display() {
	if (clear) {
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_POINTS);
		glVertex2i(CENTER.x, CENTER.y); // for some reason this is required to clear the screen?.
		glEnd();
		glFlush();
		clear = false;
	}
}

void setPixelColor(GLint x, GLint y, RGBColor color) {
	unsigned char* ptr = new unsigned char[3];
	ptr[0] = color.r;
	ptr[1] = color.g;
	ptr[2] = color.b;
	glRasterPos2i(x, y);
	glDrawPixels(1, 1, GL_RGB, GL_UNSIGNED_BYTE, ptr);
	glFlush();
	delete[] ptr;
}

RGBColor getPixelColor(GLint x, GLint y) {
	unsigned char* ptr = new unsigned char[3];
	glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, ptr);
	RGBColor color(ptr[0], ptr[1], ptr[2]);
	delete[] ptr;
	return color;
}

void floodFill(int x, int y) {
	queue < Point > Q;

	typedef pair < int, int > ii;
	set < ii > S;

	auto isValid = [](Point p) { 
		return p.x >= 0 && p.x < WIDTH && p.y >= 0 && p.y < HEIGHT; 
	};

	if (!isValid(Point(x, y))) return;
	RGBColor replacedColor = getPixelColor(x, y);
	if (replacedColor == current_color || replacedColor == BLACK) return;
	Q.push(Point(x, y));
	S.insert(ii(x, y));
	setPixelColor(x, y, current_color);
	while (!Q.empty()) {
		Point u = Q.front();
		Q.pop();
		for (const auto& dir : directions) {
			Point v = u + dir;
			if (!isValid(v) || S.count(ii(v.x, v.y)) || getPixelColor(v.x, v.y) != replacedColor) continue;
			setPixelColor(v.x, v.y, current_color);
			S.insert(ii(v.x, v.y));
			Q.push(v);
		}
	}
}

void boundaryFill(int x, int y) {
	queue < Point > Q;
	typedef pair < int, int > ii;
	set < ii > S;

	auto isValid = [](Point p) {
		return p.x >= 0 && p.x < WIDTH && p.y >= 0 && p.y < HEIGHT;
	};
	if (!isValid(Point(x, y))) return;
	setPixelColor(x, y, current_color);
	S.insert(ii(x, y));
	Q.push(Point(x, y));
	while (!Q.empty()) {
		Point u = Q.front();
		Q.pop();
		for (const auto& dir : directions) {
			Point v = u + dir;
			if (!isValid(v) || S.count(ii(v.x, v.y)) || getPixelColor(v.x, v.y) == current_color_tmp) continue;
			setPixelColor(v.x, v.y, current_color);
			S.insert(ii(v.x, v.y));
			Q.push(v);
		}
	}
}

void handleMouseEvent(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		current_position = Point(x, HEIGHT - y);
		switch (value) {
		case 1: {
			LineBresenham(current_color, current_position + Point(-50, -50), current_position + Point(50, 50)).draw();
			break;
		}
		case 2: {
			IsoscelesRightTriangle(current_position, current_color_tmp).draw();
			boundaryFill(current_position.x, current_position.y);
			IsoscelesRightTriangle(current_position, current_color).draw();
			break;
		}
		case 3: {
			EquilateralTriangle(current_position, current_color_tmp).draw();
			boundaryFill(current_position.x, current_position.y);
			EquilateralTriangle(current_position, current_color).draw();
			break;
		}
		case 4: {
			Rectangle(current_position, current_color_tmp).draw();
			boundaryFill(current_position.x, current_position.y);
			Rectangle(current_position, current_color).draw();
			break;
		}
		case 5: {
			Square(current_position, current_color_tmp).draw();
			boundaryFill(current_position.x, current_position.y);
			Square(current_position, current_color).draw();
			break;
		}
		case 6: {
			CircleMidpoint(current_color_tmp, current_position).draw();
			boundaryFill(current_position.x, current_position.y);
			CircleMidpoint(current_color, current_position).draw();
			break;
		}
		case 7: {
			ElipseMidpoint(current_color_tmp, current_position).draw();
			boundaryFill(current_position.x, current_position.y);
			ElipseMidpoint(current_color, current_position).draw();
			break;
		}
		case 8: {
			EquilateralPentagon(current_position, current_color_tmp).draw();
			boundaryFill(current_position.x, current_position.y);
			EquilateralPentagon(current_position, current_color).draw();
			break;
		}
		case 9: {
			EquilateralHexagon(current_position, current_color_tmp).draw();
			boundaryFill(current_position.x, current_position.y);
			EquilateralHexagon(current_position, current_color).draw();
			break;
		}
		case 10: {
			Arrow(current_position, current_color_tmp).draw();
			boundaryFill(current_position.x, current_position.y);
			Arrow(current_position, current_color).draw();
			break;
		}
		case 11: {
			Star(current_position, current_color_tmp).draw();
			boundaryFill(current_position.x, current_position.y);
			Star(current_position, current_color).draw();
			break;
		}
		case 12: {
			Plus(current_position, current_color_tmp).draw();
			boundaryFill(current_position.x, current_position.y);
			Plus(current_position, current_color).draw();
			break;
		}
		case 13: {
			Minus(current_position, current_color_tmp).draw();
			boundaryFill(current_position.x, current_position.y);
			Minus(current_position, current_color).draw();
			break;
		}
		case 14: {
			Multiply(current_position, current_color_tmp).draw();
			boundaryFill(current_position.x, current_position.y);
			Multiply(current_position, current_color).draw();
			break;
		}
		case 15: {
			Divide(current_position, current_color_tmp).draw();
			boundaryFill(current_position.x, current_position.y);
			Divide(current_position, current_color).draw();
			break;
		}
		case 16: {
			floodFill(current_position.x, current_position.y);
			break;
		}
		case 17: {
			floodFill(current_position.x, current_position.y);
			break;
		}
		case 18: {
			floodFill(current_position.x, current_position.y);
			break;
		}
		default: {

		}
		}
		glFlush();
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Computer Graphics");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);
	createMenu();
	glutMouseFunc(handleMouseEvent);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
