#pragma once
#include <GL/glut.h>
#include <cmath>
#include <vector>
#include "rgbcolor.h"
#include "fcoordinate.h"


namespace GlutUtility {
	bool isValid(fCoordinate p);
	void setPixelColor(int x, int y, RGBColor color);
	RGBColor getPixelColor(int x, int y);
	void drawLine(int x1, int y1, int x2, int y2, RGBColor color);
	void boundaryFill(int x, int y, RGBColor fillColor, RGBColor boundaryColor);
};


