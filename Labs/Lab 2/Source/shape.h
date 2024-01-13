#pragma once
#include <GL/glut.h>
#include <set>
using namespace std;

typedef pair < int, int > Pixel;

class Shape {
protected:
	set < Pixel > pixels;
	bool checking = false;
	bool inserting = false;
	bool prompting = true;
public:
	Shape();
	void setPixel(GLint x, GLint y);
	virtual void draw() = 0;
	virtual void drawGL() = 0;
};

class LineDDA : public Shape {
	int x1, y1, x2, y2;
public:
	LineDDA(int _x1, int _y1, int _x2, int _y2);
	void draw();
	void drawGL();
};

class LineBresenham : public Shape {
	int x1, y1, x2, y2;
public:
	LineBresenham(int _x1, int _y1, int _x2, int _y2);
	void draw();
	void drawGL();
};

class CircleMidpoint : public Shape {
	int xt, yt, r;
public:
	CircleMidpoint(int _xt, int _yt, int _r);
	void draw();
	void drawGL();
};

class ElipseMidpoint : public Shape {
	int xt, yt, a, b;
public:
	ElipseMidpoint(int _xt, int _yt, int _a, int _b);
	void draw();
	void drawGL();
};

class ParabolaMidpoint : public Shape {
	int xt, yt, f;
public:
	ParabolaMidpoint(int _xt, int _yt, int _f);
	void draw();
	void drawGL();
};

class HyperbolaMidpoint : public Shape {
	int xt, yt, a, b;
public:
	HyperbolaMidpoint(int _xt, int _yt, int _a, int _b);
	void draw();
	void drawGL();
};
