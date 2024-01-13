#include "polygon.h"
#include <iostream>
#include <queue>
#include <set>
#include "constants.h"

Polygon::Polygon(vector<Point> _vertices, RGBColor _color, Point origin) : Shape(_color) {
	for (const auto& vertex : _vertices) {
		vertices.push_back(origin + vertex);
	}
}
	
void Polygon::draw() {
	for (int i = 0; i < vertices.size(); ++i) {
		LineBresenham edge(color, vertices[i], vertices[(i + 1) % vertices.size()]);
		edge.draw();
	}
}

void Polygon::drawGL() {
	for (int i = 0; i < vertices.size(); ++i) {
		LineBresenham edge(color, vertices[i], vertices[(i + 1) % vertices.size()]);
		edge.drawGL();
	}
}

IsoscelesRightTriangle::IsoscelesRightTriangle(Point origin, RGBColor _color) 
	: Polygon({ Point(-50, -25), Point(50, -25), Point(0, 25)}, _color, origin) { }

EquilateralTriangle::EquilateralTriangle(Point origin, RGBColor _color)
	: Polygon({ Point(-43, -25), Point(43, -25), Point(0, 50) }, _color, origin) { }

Rectangle::Rectangle(Point origin, RGBColor _color)
	: Polygon({ Point(-30, -50), Point(30, -50), Point(30, 50), Point(-30, 50) }, _color, origin) { }

Square::Square(Point origin, RGBColor _color)
	: Polygon({ Point(-40, -40), Point(40, -40), Point(40, 40), Point(-40, 40) }, _color, origin) { }

EquilateralPentagon::EquilateralPentagon(Point origin, RGBColor _color)
	: Polygon({ Point(48, 15), Point(0, 50), Point(-48, 15), Point(-29, -40), Point(29, -40)}, _color, origin) { }

EquilateralHexagon::EquilateralHexagon(Point origin, RGBColor _color)
	: Polygon({ Point(50, 0), Point(25, 43), Point(-25, 43), Point(-50, 0), Point(-25, -43), Point(25, -43) }, _color, origin) { }

Arrow::Arrow(Point origin, RGBColor _color)
	: Polygon({ Point(-25, -50), Point(25, -50), Point(25, 0), Point(50, 0), Point(0, 50), Point(-50, 0), Point(-25, 0) }, _color, origin) { }

Star::Star(Point origin, RGBColor _color)
	: Polygon({ Point(48, 15), Point(11, 15), Point(0, 50), Point(-11, 15), Point(-48, 15), Point(-18, -6), Point(-29, -40), Point(0, -19), Point(29, -40), Point(18, -6) }, _color, origin) { }

Plus::Plus(Point origin, RGBColor _color)
	: Polygon({ Point(-12, -50), Point(12, -50), Point(12, -12), Point(50, -12), Point(50, 12), Point(12, 12), Point(12, 50), Point(-12, 50), Point(-12, 12), Point(-50, 12), Point(-50, -12), Point(-12, -12) }, _color, origin) { }

Minus::Minus(Point origin, RGBColor _color)
	: Polygon({ Point(-50, -12), Point(50, -12), Point(50, 12), Point(-50, 12) }, _color, origin) { }

Multiply::Multiply(Point origin, RGBColor _color)
	: Polygon({ Point(40, 30), Point(30, 40), Point(0, 10), Point(-30, 40), Point(-40, 30), Point(-10, 0), Point(-40, -30), Point(-30, -40), Point(0, -10), Point(30, -40), Point(40, -30), Point(10, 0) }, _color, origin) { }

Divide::Divide(Point origin, RGBColor _color)
	: Polygon({ Point(40, 30), Point(30, 40), Point(-40, -30), Point(-30, -40) }, _color, origin) { }