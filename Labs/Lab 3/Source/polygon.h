#pragma once
#include "shape.h"

class Polygon : public Shape {
protected:
	vector < Point > vertices;
public:
	Polygon(vector < Point > _vertices, RGBColor _color, Point origin = { 0, 0 });
	void draw();
	void drawGL();
	virtual ~Polygon() = default;
};

class IsoscelesRightTriangle : public Polygon {
public:
	IsoscelesRightTriangle(Point origin, RGBColor _color);
};

class EquilateralTriangle : public Polygon {
public:
	EquilateralTriangle(Point origin, RGBColor _color);
};

class Rectangle : public Polygon {
public:
	Rectangle(Point origin, RGBColor _color);
};

class Square : public Polygon {
public:
	Square(Point origin, RGBColor _color);
};

class EquilateralPentagon : public Polygon {
public:
	EquilateralPentagon(Point origin, RGBColor _color);
};

class EquilateralHexagon : public Polygon {
public:
	EquilateralHexagon(Point origin, RGBColor _color);
};

class Arrow : public Polygon {
public:
	Arrow(Point origin, RGBColor _color);
};

class Star : public Polygon {
public:
	Star(Point origin, RGBColor _color);
};

class Plus : public Polygon {
public:
	Plus(Point origin, RGBColor _color);
};

class Minus : public Polygon {
public:
	Minus(Point origin, RGBColor _color);
};

class Multiply : public Polygon {
public:
	Multiply(Point origin, RGBColor _color);
};

class Divide : public Polygon {
public:
	Divide(Point origin, RGBColor _color);
};

