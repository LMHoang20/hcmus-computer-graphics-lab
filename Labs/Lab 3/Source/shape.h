#pragma once
#include <GL/glut.h>
#include <vector>

using namespace std;

struct Point {
	int x, y;
	Point(int _x, int _y);
	Point operator+(const Point& other);
};

struct RGBColor {
	unsigned char r, g, b;
	RGBColor(unsigned char _r, unsigned char _g, unsigned char _b);
	RGBColor(const RGBColor& other);
	bool operator!=(const RGBColor& other);
	bool operator==(const RGBColor& other);
};

class Shape {
protected:
	RGBColor color;
public:
	Shape(RGBColor _color);
	void setPixel(GLint x, GLint y);
	virtual void draw() = 0;
	virtual void drawGL() = 0;
	virtual ~Shape() = default;
};

class LineDDA : public Shape {
	int x1, y1, x2, y2;
public:
	LineDDA(RGBColor _color, int _x1, int _y1, int _x2, int _y2);
	LineDDA(RGBColor _color, Point A, Point B);
	void draw();
	void drawGL();
};

class LineBresenham : public Shape {
	int x1, y1, x2, y2;
public:
	LineBresenham(RGBColor _color, int _x1, int _y1, int _x2, int _y2);
	LineBresenham(RGBColor _color, Point A, Point B);
	void draw();
	void drawGL();
};

#define DEFAULT_CIRCLE_R 25

class CircleMidpoint : public Shape {
	int xt, yt, r;
public:
	CircleMidpoint(RGBColor _color, int _xt, int _yt, int _r = DEFAULT_CIRCLE_R);
	CircleMidpoint(RGBColor _color, Point _center, int _r = DEFAULT_CIRCLE_R);
	void draw();
	void drawGL();
};

#define DEFAULT_ELLIPSE_A 30
#define DEFAULT_ELLIPSE_B 20

class ElipseMidpoint : public Shape {
	int xt, yt, a, b;
public:
	ElipseMidpoint(RGBColor _color, int _xt, int _yt, int _a = DEFAULT_ELLIPSE_A, int _b = DEFAULT_ELLIPSE_B);
	ElipseMidpoint(RGBColor _color, Point _center, int _a = DEFAULT_ELLIPSE_A, int _b = DEFAULT_ELLIPSE_B);
	void draw();
	void drawGL();
};

class ParabolaMidpoint : public Shape {
	int xt, yt, f;
public:
	ParabolaMidpoint(RGBColor _color, int _xt, int _yt, int _f);
	ParabolaMidpoint(RGBColor _color, Point _center, int _f);
	void draw();
	void drawGL();
};

class HyperbolaMidpoint : public Shape {
	int xt, yt, a, b;
public:
	HyperbolaMidpoint(RGBColor _color, int _xt, int _yt, int _a, int _b);
	HyperbolaMidpoint(RGBColor _color, Point _center, int _a, int _b);
	void draw();
	void drawGL();
};