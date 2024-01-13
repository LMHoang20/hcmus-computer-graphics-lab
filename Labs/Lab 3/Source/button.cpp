#include "button.h"
#include <iostream>
#include "shape.h"
#include "constants.h"

using namespace std;

Button::Button(int _left, int _bottom, int _right, int _top, string _text) : left(_left), right(_right), bottom(_bottom), top(_top), text(_text) { }

void Button::draw() {
	glColor3ub(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2i(left, bottom);
	glVertex2i(left, top);
	glVertex2i(left, bottom);
	glVertex2i(right, bottom);
	glVertex2i(right, bottom);
	glVertex2i(right, top);
	glVertex2i(left, top);
	glVertex2i(right, top);
	glEnd();
	glRasterPos2i((left + right - FONT_SIZE * text.size() / 2) / 2, (bottom + top - FONT_SIZE / 2) / 2);
	for(const auto& c : text) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, c);
	}
	glFlush();
}

bool Button::collision(int x, int y) {
	return left <= x && x <= right && bottom <= y && y <= top;
}

