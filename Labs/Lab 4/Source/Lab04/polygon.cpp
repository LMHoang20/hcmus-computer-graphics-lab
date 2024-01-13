#include "polygon.h"
#include "glututility.h"
#include "constants.h"
#include <iostream>

Polygon::Polygon(std::vector<fCoordinate> _vertices, RGBColor _color)
	: vertices(_vertices), color(_color), center(0, 0) { }

RGBColor Polygon::getColor()
{
	return color;
}

void Polygon::addVertex(fCoordinate vertex)
{
	vertices.push_back(vertex);
}

Polygon::Polygon(std::vector<fCoordinate> _vertices, fCoordinate bound1, fCoordinate bound2, RGBColor _color)
	: vertices(_vertices), color(_color), center((bound1 + bound2) * 0.5) 
{
	fCoordinate dir = (bound2 - bound1) * 0.5;
	translate(center);
	scale(center, dir.x, dir.y);
}

void Polygon::drawLastEdge()
{
	if (vertices.size() < 2) return;
	int i = vertices.size() - 1;
	int j = vertices.size() - 2;
}

void Polygon::drawEdge(int vertex1, int vertex2, RGBColor color)
{
	if (vertex1 < 0 || vertex1 >= vertices.size()) return;
	if (vertex2 < 0 || vertex2 >= vertices.size()) return;
	GlutUtility::drawLine(vertices[vertex1].x, vertices[vertex1].y, vertices[vertex2].x, vertices[vertex2].y, color);
}

void Polygon::drawVertices(RGBColor color)
{
	glColor3ub(color.r, color.g, color.b);
	glPointSize(3);
	glBegin(GL_POINTS);
	for (const auto& vertex : vertices) {
		glVertex2i(vertex.x, vertex.y);
	}
	glEnd();
	glFlush();
}

void Polygon::draw()
{
	int n = vertices.size();
	for (int i = 0; i < n; ++i) {
		drawEdge(i, (i + 1) % n, color);
	}
	glFlush();
}

void Polygon::eraseVertices()
{
	glColor3ub(backgroundColor.r, backgroundColor.g, backgroundColor.b);
	glPointSize(3);
	glBegin(GL_POINTS);
	for (const auto& vertex : vertices) {
		glVertex2i(vertex.x, vertex.y);
	}
	glEnd();
	glFlush();
}

void Polygon::erase()
{
	int n = vertices.size();
	for (int i = 0; i < n; ++i) {
		drawEdge(i, (i + 1) % n, backgroundColor);
	}
	glFlush();
}

void Polygon::translate(fCoordinate dir)
{
	for (auto& vertex : vertices) {
		vertex.translate(dir);
	}
}

void Polygon::rotate(fCoordinate pivot, float degree)
{	
	for (auto& vertex : vertices) {
		vertex.rotate(pivot, degree);
	}
}

void Polygon::scale(fCoordinate pivot, float scaleFactorX, float scaleFactorY)
{
	for (auto& vertex : vertices) {
		vertex.scale(pivot, scaleFactorX, scaleFactorY);
	}
}

IsoscelesRightTriangle::IsoscelesRightTriangle(fCoordinate bound1, fCoordinate bound2, RGBColor _color)
	: Polygon({ fCoordinate(1, 0), fCoordinate(0, 1), fCoordinate(-1, 0) }, 
		makeSquareBound(bound1, bound2).first,
		makeSquareBound(bound1, bound2).second,
		_color)
{ }

EquilateralTriangle::EquilateralTriangle(fCoordinate bound1, fCoordinate bound2, RGBColor _color)
	: Polygon({ fCoordinate(0.86602540378, -0.5), fCoordinate(0, 1), fCoordinate(-0.86602540378, -0.5) }, 
		makeSquareBound(bound1, bound2).first, 
		makeSquareBound(bound1, bound2).second, 
		_color)
{ }

Rectangle::Rectangle(fCoordinate bound1, fCoordinate bound2, RGBColor _color)
	: Polygon({ fCoordinate(1, 1), fCoordinate(-1, 1), fCoordinate(-1, -1), fCoordinate(1, -1) }, 
		bound1, 
		bound2, 
		_color) 
{ }

Square::Square(fCoordinate bound1, fCoordinate bound2, RGBColor _color)
	: Polygon({ fCoordinate(1, 1), fCoordinate(-1, 1), fCoordinate(-1, -1), fCoordinate(1, -1) }, 
		makeSquareBound(bound1, bound2).first,
		makeSquareBound(bound1, bound2).second,
		_color) 
{ }

EquilateralPentagon::EquilateralPentagon(fCoordinate bound1, fCoordinate bound2, RGBColor _color)
	: Polygon({ 
		fCoordinate(0.951056516295, 0.309016994375), fCoordinate(0, 1), fCoordinate(-0.951056516295, 0.309016994375), 
		fCoordinate(-0.587785252292, -0.809016994375), fCoordinate(0.587785252292, -0.809016994375) },
		makeSquareBound(bound1, bound2).first,
		makeSquareBound(bound1, bound2).second,
		_color) 
{ }

EquilateralHexagon::EquilateralHexagon(fCoordinate bound1, fCoordinate bound2, RGBColor _color)
	: Polygon({ 
		fCoordinate(1, 0), fCoordinate(0.5, 0.866025403784), fCoordinate(-0.5, 0.866025403784), 
		fCoordinate(-1, 0), fCoordinate(-0.5, -0.866025403784), fCoordinate(0.5, -0.866025403784) },
		makeSquareBound(bound1, bound2).first,
		makeSquareBound(bound1, bound2).second,
		_color) 
{ }

Arrow::Arrow(fCoordinate bound1, fCoordinate bound2, RGBColor _color)
	: Polygon({
		fCoordinate(1, 0), fCoordinate(0, 1), fCoordinate(-1, 0), fCoordinate(-0.5, 0), 
		fCoordinate(-0.5, -1), fCoordinate(0.5, -1), fCoordinate(0.5, 0) },
		bound1, 
		bound2, 
		_color) 
{ }

Star::Star(fCoordinate bound1, fCoordinate bound2, RGBColor _color)
	: Polygon({ 
		fCoordinate(0.951056516295, 0.309016994375), fCoordinate(0.22451398829, 0.309016994375), fCoordinate(0, 1),
		fCoordinate(-0.22451398829, 0.309016994375), fCoordinate(-0.951056516295, 0.309016994375), fCoordinate(-0.363271264, -0.11803398875),
		fCoordinate(-0.587785252292,-0.809016994375), fCoordinate(0, -0.38196601125), fCoordinate(0.587785252292,-0.809016994375), fCoordinate(0.363271264, -0.11803398875) },
		bound1, 
		bound2, 
		_color) 
{ }

Plus::Plus(fCoordinate bound1, fCoordinate bound2, RGBColor _color)
	: Polygon({ 
		fCoordinate(1, 0.25), fCoordinate(0.25, 0.25), fCoordinate(0.25, 1), fCoordinate(-0.25, 1), fCoordinate(-0.25, 0.25), fCoordinate(-1, 0.25), 
		fCoordinate(-1, -0.25), fCoordinate(-0.25, -0.25), fCoordinate(-0.25, -1), fCoordinate(0.25, -1), fCoordinate(0.25, -0.25), fCoordinate(1, -0.25) },
		bound1, 
		bound2, 
		_color) 
{ }

Minus::Minus(fCoordinate bound1, fCoordinate bound2, RGBColor _color)
	: Polygon({ fCoordinate(1, 0.25), fCoordinate(-1, 0.25), fCoordinate(-1, -0.25), fCoordinate(1, -0.25) },
		bound1, 
		bound2, 
		_color) 
{ }

Multiply::Multiply(fCoordinate bound1, fCoordinate bound2, RGBColor _color)
	: Polygon({ fCoordinate(0.8, 0.6), fCoordinate(0.6, 0.8), fCoordinate(0, 0.2), fCoordinate(-0.6, 0.8), fCoordinate(-0.8, 0.6), fCoordinate(-0.2, 0), 
		fCoordinate(-0.8, -0.6), fCoordinate(-0.6, -0.8), fCoordinate(0, -0.2), fCoordinate(0.6, -0.8), fCoordinate(0.8, -0.6), fCoordinate(0.2, 0) }, 
		bound1, 
		bound2, 
		_color) 
{ }

Divide::Divide(fCoordinate bound1, fCoordinate bound2, RGBColor _color)
	: Polygon({ fCoordinate(0.8, 0.6), fCoordinate(0.6, 0.8), fCoordinate(-0.8, -0.6), fCoordinate(-0.6, -0.8) }, 
		bound1, 
		bound2, 
		_color) 
{ }