#pragma once
#include "fcoordinate.h"
#include "rgbcolor.h"
#include <vector>
#include <utility>
#include <GL/glut.h>

class Polygon {
protected:
	std::vector < fCoordinate > vertices;
	RGBColor color;
	fCoordinate center;
public:
	Polygon(std::vector < fCoordinate > _vertices, fCoordinate bound1, fCoordinate bound2, RGBColor _color);
	Polygon(std::vector < fCoordinate > _vertices, RGBColor _color);
	RGBColor getColor();
	void addVertex(fCoordinate vertex);
	void drawLastEdge();
	void drawEdge(int vertex1, int vertex2, RGBColor color);
	void drawVertices(RGBColor color);
	void draw();
	void eraseVertices();
	void erase();
	void translate(fCoordinate dir);
	void rotate(fCoordinate pivot, float degree);
	void scale(fCoordinate pivot, float scaleFactorX, float scaleFactorY);
	virtual ~Polygon() = default;
};

class IsoscelesRightTriangle : public Polygon {
public:
	IsoscelesRightTriangle(fCoordinate bound1, fCoordinate bound2, RGBColor _color);
};

class EquilateralTriangle : public Polygon {
public:
	EquilateralTriangle(fCoordinate bound1, fCoordinate bound2, RGBColor _color);
};

class Rectangle : public Polygon {
public:
	Rectangle(fCoordinate bound1, fCoordinate bound2, RGBColor _color);
};

class Square : public Polygon {
public:
	Square(fCoordinate bound1, fCoordinate bound2, RGBColor _color);
};

class EquilateralPentagon : public Polygon {
public:
	EquilateralPentagon(fCoordinate bound1, fCoordinate bound2, RGBColor _color);
};

class EquilateralHexagon : public Polygon {
public:
	EquilateralHexagon(fCoordinate bound1, fCoordinate bound2, RGBColor _color);
};

class Arrow : public Polygon {
public:
	Arrow(fCoordinate bound1, fCoordinate bound2, RGBColor _color);
};

class Star : public Polygon {
public:
	Star(fCoordinate bound1, fCoordinate bound2, RGBColor _color);
};

class Plus : public Polygon {
public:
	Plus(fCoordinate bound1, fCoordinate bound2, RGBColor _color);
};

class Minus : public Polygon {
public:
	Minus(fCoordinate bound1, fCoordinate bound2, RGBColor _color);
};

class Multiply : public Polygon {
public:
	Multiply(fCoordinate bound1, fCoordinate bound2, RGBColor _color);
};

class Divide : public Polygon {
public:
	Divide(fCoordinate bound1, fCoordinate bound2, RGBColor _color);
};

