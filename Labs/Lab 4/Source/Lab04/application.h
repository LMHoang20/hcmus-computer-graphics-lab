#pragma once
#include <vector>
#include <set>
#include "polygon.h"
#include "rgbcolor.h"

class Application {
	std::vector < Polygon* > polygons;
	std::set < RGBColor, RGBCompare > availableColors;
public:
	Application();
	void insertPolygon(Polygon* polygon, RGBColor color);
	RGBColor getRandomAvailableColor();
	Polygon* getPolygonWithColor(RGBColor color);
	Polygon* getPolygonWithId(int idx);
	void drawEverything();
	void clearEverything();
	~Application();
};