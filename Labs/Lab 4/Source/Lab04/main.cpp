#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "glututility.h"
#include "constants.h"
#include "polygon.h"
#include "rgbcolor.h"
#include "fcoordinate.h"
#include "application.h"


static int window;
static int value = 0;

RGBColor WHITE(255, 255, 255);
const auto CENTER = fCoordinate(WIDTH * 0.5, HEIGHT * 0.5);

fCoordinate* prevPoint = nullptr;
Application* app = nullptr;
Polygon* curSelectedPolygon = nullptr;
Polygon* curDrawingPolygon = nullptr;
int eraseAllMenuId = 0;
int menu_id = 0;

std::vector < int > ids;
std::vector < std::vector < std::string > > submenu_labels = {
	{ },
	{ "Vuong can", "Deu" },
	{ "Hinh chu nhat", "Hinh vuong" },
	{ "Ngu giac deu", "Luc giac deu" },
	{ "Mui ten", "Ngoi sao" },
	{ "Cong", "Tru", "Nhan", "Chia" },
	{ },
	{ }
};
std::vector < std::string > menu_labels = {
	"Da giac", 
	"Tam giac", 
	"Tu giac", 
	"Da giac deu", 
	"Hinh khac", 
	"Dau", 
	"Chon hinh", 
	"Xoa tat ca"
};
std::vector < std::string >* selectShapeMenu = &submenu_labels[6];

void menu(int num) {
	value = num;
	if (prevPoint) {
		delete prevPoint;
		prevPoint = nullptr;
	}
	curDrawingPolygon = nullptr;
	if (num == ids.back()) {
		app->clearEverything();
		selectShapeMenu->clear();
		curSelectedPolygon = nullptr;
		glutPostRedisplay();
	}
	else if (num >= 14) {
		int polygonChoice = num - 14;
		curSelectedPolygon = app->getPolygonWithId(polygonChoice);
		if (curSelectedPolygon) {
			glutPostRedisplay();
		}
	}
}

int createSubmenuEntries(std::vector < std::string > labels, int start_index) {
	int submenu_id = glutCreateMenu(menu);
	for (int i = 0; i < labels.size(); ++i) {
		glutAddMenuEntry(labels[i].c_str(), start_index + i);
	}
	return submenu_id;
}

void createMenu(void) {
	ids.clear();
	for (int i = 0, id = 1; i < menu_labels.size(); ++i) {
		if (submenu_labels[i].empty()) {
			ids.push_back(id);
			id += 1;
		}
		else {
			ids.push_back(createSubmenuEntries(submenu_labels[i], id));
			id += submenu_labels[i].size();
		}
	}
	menu_id = glutCreateMenu(menu);
	for (int i = 0; i < menu_labels.size(); ++i) {
		if (submenu_labels[i].empty()) {
			glutAddMenuEntry(menu_labels[i].c_str(), ids[i]);
		}
		else {
			glutAddSubMenu(menu_labels[i].c_str(), ids[i]);
		}
	}
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void display() {	
	glutDestroyMenu(menu_id);
	createMenu();
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3ub(WHITE.r, WHITE.g, WHITE.b);
	glPointSize(3);
	glBegin(GL_POINTS);
	glVertex2i(CENTER.x, CENTER.y);
	glEnd();
	app->drawEverything();
	if (curSelectedPolygon) {
		curSelectedPolygon->drawVertices(WHITE);
	}
	glFlush();
}

void addNewPolygon(Polygon* polygon, RGBColor color) {
	app->insertPolygon(polygon, color);
	selectShapeMenu->push_back(color);
	glutDestroyMenu(menu_id);
	createMenu();
}


void handleMouseEvent(int button, int state, int x, int y) {
	y = HEIGHT - y;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (value == 0) return;
		if (value == 1) { // Draw new polygon
			fCoordinate* curPoint = new fCoordinate(x, y);
			RGBColor color = app->getRandomAvailableColor();
			if (curSelectedPolygon) {
				/*
				curSelectedPolygon->eraseVertices();
				curSelectedPolygon->draw();
				*/
			}
			if (!curDrawingPolygon) {
				curDrawingPolygon = new Polygon({}, color);
				addNewPolygon(curDrawingPolygon, color);
				curSelectedPolygon = curDrawingPolygon;
			}
			else {
				/*
				curDrawingPolygon->erase();
				curDrawingPolygon->eraseVertices();
				*/
			}
			
			curDrawingPolygon->addVertex(*curPoint);
			/*
			curDrawingPolygon->draw();
			curDrawingPolygon->drawVertices(WHITE);
			*/
			delete curPoint;
			curPoint = nullptr;
			display();
			return;
		}
		if (value >= 2 && value <= 13) { // Create new polygon
			if (prevPoint == nullptr) {
				prevPoint = new fCoordinate(x, y);
				return;
			}
			fCoordinate* curPoint = new fCoordinate(x, y);
			RGBColor color = app->getRandomAvailableColor();
			Polygon* polygon = nullptr;
			switch (value) {
			case 2: {
				polygon = new IsoscelesRightTriangle(*prevPoint, *curPoint, color);
				break;
			}
			case 3: {
				polygon = new EquilateralTriangle(*prevPoint, *curPoint, color);
				break;
			}
			case 4: {
				polygon = new Rectangle(*prevPoint, *curPoint, color);
				break;
			}
			case 5: {
				polygon = new Square(*prevPoint, *curPoint, color);				
				break;
			}
			case 6: {				
				polygon = new EquilateralPentagon(*prevPoint, *curPoint, color);				
				break;
			}
			case 7: {
				polygon = new EquilateralHexagon(*prevPoint, *curPoint, color);
				break;
			}
			case 8: {
				polygon = new Arrow(*prevPoint, *curPoint, color);
				break;
			}
			case 9: {
				polygon = new Star(*prevPoint, *curPoint, color);
				break;
			}
			case 10: {
				polygon = new Plus(*prevPoint, *curPoint, color);
				break;
			}
			case 11: {
				polygon = new Minus(*prevPoint, *curPoint, color);
				break;
			}
			case 12: {
				polygon = new Multiply(*prevPoint, *curPoint, color);
				break;
			}
			case 13: {
				polygon = new Divide(*prevPoint, *curPoint, color);
				break;
			}
			default: {
				break;
			}
			}
			/*
			if (curSelectedPolygon) {
				curSelectedPolygon->erase();
				curSelectedPolygon->eraseVertices();
				curSelectedPolygon->draw();
			}
			*/
			curSelectedPolygon = polygon;
			/*
			curSelectedPolygon->draw();
			curSelectedPolygon->drawVertices(WHITE);
			*/
			addNewPolygon(polygon, color);
			delete prevPoint;
			delete curPoint;
			prevPoint = nullptr;
			curPoint = nullptr;
			display();
			return;
		}
	}
}

void handleKeyboardEvent(unsigned char key, int x, int y) {
	if (!curSelectedPolygon) return;
	if (key != 'l' && key != 'r' && key != '+' && key != '-') return;
	/*
	curSelectedPolygon->erase();
	curSelectedPolygon->eraseVertices();
	*/
	switch (key) {
	case 'l': {
		curSelectedPolygon->rotate(CENTER, 1);
		break;
	}
	case 'r': {
		curSelectedPolygon->rotate(CENTER, -1);
		break;
	}
	case '+': {
		curSelectedPolygon->scale(CENTER, 1.1, 1.1);
		break;
	}
	case '-': {
		curSelectedPolygon->scale(CENTER, 1 / 1.1, 1 / 1.1);
		break;
	}
	default:
	{
		return;
	}
	}
	/*
	curSelectedPolygon->draw();
	curSelectedPolygon->drawVertices(WHITE);
	*/
	display();
}

void handleSpecialEvent(int key, int x, int y) {
	if (!curSelectedPolygon) return;
	if (key != GLUT_KEY_LEFT && key != GLUT_KEY_RIGHT && key != GLUT_KEY_UP && key != GLUT_KEY_DOWN) return;
	/*
	curSelectedPolygon->erase();
	curSelectedPolygon->eraseVertices();
	*/
	switch (key) {
	case GLUT_KEY_LEFT: {
		curSelectedPolygon->translate(LEFT);
		break;
	}
	case GLUT_KEY_RIGHT: {
		curSelectedPolygon->translate(RIGHT);
		break;
	}
	case GLUT_KEY_UP: {
		curSelectedPolygon->translate(UP);
		break;
	}
	case GLUT_KEY_DOWN: {
		curSelectedPolygon->translate(DOWN);
		break;
	}
	}
	/*
	curSelectedPolygon->draw();
	curSelectedPolygon->drawVertices(WHITE);
	*/
	display();
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
	glPointSize(3);
	glutMouseFunc(handleMouseEvent);
	glutKeyboardFunc(handleKeyboardEvent);
	glutSpecialFunc(handleSpecialEvent);
	glutDisplayFunc(display);
	app = new Application();
	glutMainLoop();
	return 0;
}
