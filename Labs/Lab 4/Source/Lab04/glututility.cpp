#include "fcoordinate.h"
#include "glututility.h"
#include "constants.h"
#include <queue>
#include <set>


void GlutUtility::setPixelColor(int x, int y, RGBColor color) {
	if (!isValid(fCoordinate(x, y))) return;
	unsigned char* ptr = new unsigned char[3];
	ptr[0] = color.r;
	ptr[1] = color.g;
	ptr[2] = color.b;
	glRasterPos2i(x, y);
	glDrawPixels(1, 1, GL_RGB, GL_UNSIGNED_BYTE, ptr);
	glFlush();
	delete[] ptr;
	/*
	glColor3b(color.r, color.g, color.b);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
	*/
}

RGBColor GlutUtility::getPixelColor(int x, int y) {
	if (!isValid(fCoordinate(x, y))) return RGBColor(0, 0, 0);
	unsigned char* ptr = new unsigned char[3];
	glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, ptr);
	RGBColor color(ptr[0], ptr[1], ptr[2]);
	delete[] ptr;
	return color;
}

void GlutUtility::drawLine(int x1, int y1, int x2, int y2, RGBColor color) {
	glColor3ub(color.r, color.g, color.b);
	glPointSize(1);
	glBegin(GL_LINES);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glEnd();
	glFlush();
}

bool GlutUtility::isValid(fCoordinate p) {
	return p.x >= 0 && p.x < WIDTH && p.y >= 0 && p.y < HEIGHT;
};

void GlutUtility::boundaryFill(int x, int y, RGBColor fillColor, RGBColor boundaryColor) {
	std::queue < fCoordinate > Q;
	typedef std::pair < int, int > ii;
	std::set < ii > S;
	if (!isValid(fCoordinate(x, y))) return;
	setPixelColor(x, y, fillColor);
	S.insert(ii(x, y));
	Q.push(fCoordinate(x, y));
	while (!Q.empty()) {
		fCoordinate u = Q.front();
		Q.pop();
		for (const auto& dir : directions) {
			fCoordinate v = u + dir;
			if (!isValid(v) || S.count(ii(v.x, v.y)) || getPixelColor(v.x, v.y) == boundaryColor) continue;
			setPixelColor(v.x, v.y, fillColor);
			S.insert(ii(v.x, v.y));
			Q.push(v);
		}
	}
}