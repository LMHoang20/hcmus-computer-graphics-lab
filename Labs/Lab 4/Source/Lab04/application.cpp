#include "application.h"
#include "glututility.h"
#include "constants.h"
#include <random>
#include <iostream>

Application::Application() {
	while (availableColors.size() < 100) {
		int r = rand() % 128 + 128;
		int g = rand() % 128 + 128;	
		int b = rand() % 128 + 128;
		RGBColor color(r, g, b);
		if (color == defaultBoundaryColor) continue;
		availableColors.insert(color);
	}
}

void Application::insertPolygon(Polygon* polygon, RGBColor color) {
	polygons.push_back(polygon);
	availableColors.erase(color);
}

RGBColor Application::getRandomAvailableColor() {
	int i = rand() % availableColors.size();
	auto itr = availableColors.begin();
	std::advance(itr, i);
	return *itr;
}

Polygon* Application::getPolygonWithColor(RGBColor color) {
	return nullptr;
}

Polygon* Application::getPolygonWithId(int idx)
{
	if (idx < 0 || idx >= polygons.size()) return nullptr;
	return polygons[idx];
}

void Application::drawEverything() {
	for (const auto& polygon : polygons) {
		polygon->draw();
	}
}

void Application::clearEverything() {
	for (auto& polygon : polygons) {
		delete polygon;
	}
	polygons.clear();
	while (availableColors.size() < 100) {
		int r = rand() % 128 + 128;
		int g = rand() % 128 + 128;
		int b = rand() % 128 + 128;
		RGBColor color(r, g, b);
		if (color == defaultBoundaryColor) continue;
		availableColors.insert(color);
	}
}

Application::~Application() {
	for (auto& polygon : polygons) {
		delete polygon;
	}
	polygons.clear();
}
