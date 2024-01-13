#include "shape.h"
#include <iostream>
#include "constants.h"
#include <cmath>
#include <chrono>

Shape::Shape() { }

void Shape::setPixel(GLint x, GLint y) {
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return;
	if (checking) {
		if (pixels.count(Pixel(x, y))) glColor3ub(0, 255, 0);
		else glColor3ub(255, 0, 0);	
	}
	else if (inserting) {
		glColor3ub(0, 0, 0);
		pixels.insert(Pixel(x, y));
	}
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

LineDDA::LineDDA(int _x1, int _y1, int _x2, int _y2) : x1(_x1), y1(_y1), x2(_x2), y2(_y2) { }

LineBresenham::LineBresenham(int _x1, int _y1, int _x2, int _y2) : x1(_x1), y1(_y1), x2(_x2), y2(_y2) { }

CircleMidpoint::CircleMidpoint(int _xt, int _yt, int _r) : xt(_xt), yt(_yt), r(_r) { }

ElipseMidpoint::ElipseMidpoint(int _xt, int _yt, int _a, int _b) : xt(_xt), yt(_yt), a(_a), b(_b) { }

ParabolaMidpoint::ParabolaMidpoint(int _xt, int _yt, int _f) : xt(_xt), yt(_yt), f(_f) { }

HyperbolaMidpoint::HyperbolaMidpoint(int _xt, int _yt, int _a, int _b) : xt(_xt), yt(_yt), a(_a), b(_b) { }

void LineDDA::draw() {
	if (prompting) cout << "Drawing LineDDA: ";
	
	int dx = abs(x1 - x2);
	int dy = abs(y1 - y2);

	if (!dx && !dy) {
		setPixel(x1, y1);
		glFlush();
		return;
	}

	if (!dx) {
		if (y1 > y2) {
			swap(x1, x2);
			swap(y1, y2);
		}
		for (int y = y1; y <= y2; ++y) setPixel(x1, y);
		glFlush();
		return;
	}

	if (!dy) {
		if (x1 > x2) {
			swap(x1, x2);
			swap(y1, y2);
		}
		for (int x = x1; x <= x2; ++x) setPixel(x, y1);
		glFlush();
		return;
	}

	if (dy < dx) {
		if (x1 > x2) {
			swap(x1, x2);
			swap(y1, y2);
		}
		int x = x1;
		float y = y1;
		float m = 1.0 * (y2 - y1) / (x2 - x1);
		setPixel(x, round(y));
		while (x < x2) {
			x += 1;
			y += m;
			setPixel(x, round(y));
		}
	}
	else {
		if (y1 > y2) {
			swap(x1, x2);
			swap(y1, y2);
		}
		float x = x1;
		int y = y1;
		float m = 1.0 * (x2 - x1) / (y2 - y1);
		while (y < y2) {
			y += 1;
			x += m;
			setPixel(round(x), y);
		}
	}

	glFlush();
}

void LineDDA::drawGL() {
	auto start = chrono::high_resolution_clock::now();
	glColor3ub(0, 255, 0);
	glBegin(GL_LINES);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glEnd();
	glFlush();
	auto stop = chrono::high_resolution_clock::now();
	cout << "LineGL: ";
	cout << chrono::duration_cast<chrono::microseconds>(stop - start).count() << " microseconds\n";
}

void LineBresenham::draw() {
	if (prompting) cout << "Drawing LineBresenham: ";
	
	int dx = abs(x1 - x2);
	int dy = abs(y1 - y2);

	if (dx == 0 && dy == 0) {
		setPixel(x1, y1);
		glFlush();
		return;
	}

	if (dx == 0) {
		if (y1 > y2) {
			swap(x1, x2);
			swap(y1, y2);
		}
		for (int y = y1; y <= y2; ++y) setPixel(x1, y);
		glFlush();
		return;
	}

	if (dy == 0) {
		if (x1 > x2) {
			swap(x1, x2);
			swap(y1, y2);
		}
		for (int x = x1; x <= x2; ++x) setPixel(x, y1);
		glFlush();
		return;
	}

	if (dy < dx) {
		if (x1 > x2) {
			swap(x1, x2);
			swap(y1, y2);
		}
		const int d = y1 < y2 ? 1 : -1;
		int x = x1;
		int y = y1;
		int p = 2 * dy - dx;
		const int c1 = 2 * dy;
		const int c2 = 2 * (dy - dx);
		setPixel(x, y);
		while (x < x2) {
			x += 1;
			if (p < 0) p += c1;
			else p += c2, y += d;
			setPixel(x, y);
		}
	}
	else {
		if (y1 > y2) {
			swap(x1, x2);
			swap(y1, y2);
		}
		const int d = x1 < x2 ? 1 : -1;
		int x = x1;
		int y = y1;
		int p = 2 * dx - dy;
		const int c1 = 2 * dx;
		const int c2 = 2 * (dx - dy);
		setPixel(x, y);
		while (y < y2) {
			y += 1;
			if (p < 0) p += c1;
			else p += c2, x += d;
			setPixel(x, y);
		}
	}

	glFlush();
}

void LineBresenham::drawGL() {
	auto start = chrono::high_resolution_clock::now();
	glColor3ub(0, 255, 0);
	glBegin(GL_LINES);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glEnd();
	glFlush();
	auto stop = chrono::high_resolution_clock::now();
	cout << "Drawing LineGL: ";
	cout << chrono::duration_cast<chrono::microseconds>(stop - start).count() << " microseconds\n";
}

void CircleMidpoint::draw() {
	if (prompting) cout << "Drawing CircleMidpoint: ";
	
	if (r == 0) {
		setPixel(xt, yt);
		glFlush();
		return;
	}
	int x = 0;
	int y = r;
	int p = 5 - 4 * r;

	setPixel(xt + x, yt + y);
	setPixel(xt - x, yt + y);
	setPixel(xt + x, yt - y);
	setPixel(xt - x, yt - y);
	setPixel(xt + y, yt + x);
	setPixel(xt - y, yt + x);
	setPixel(xt + y, yt - x);
	setPixel(xt - y, yt - x);

	while (x < y) {
		x += 1;
		if (p < 0) p += 4 * (2 * x + 1);
		else {
			y -= 1;
			p += 4 * (2 * x + 1 - 2 * y);
		}
		
		setPixel(xt + x, yt + y);
		setPixel(xt - x, yt + y);
		setPixel(xt + x, yt - y);
		setPixel(xt - x, yt - y);
		setPixel(xt + y, yt + x);
		setPixel(xt - y, yt + x);
		setPixel(xt + y, yt - x);
		setPixel(xt - y, yt - x);
	}

	glFlush();
}

void CircleMidpoint::drawGL() {
	pixels.clear();
	prompting = false;
	inserting = true;
	this->draw();
	prompting = true;
	inserting = false;
	checking = true;
	auto start = chrono::high_resolution_clock::now();
	float t = 0;
	while (t < 2 * pi) {
		float x = r * cos(t);
		float y = r * sin(t);
		t += 0.001;
		setPixel(round(xt + x), round(yt + y));
	}
	checking = false;
	glFlush();
	auto stop = chrono::high_resolution_clock::now();
	cout << "Drawing CircleGL: ";
	cout << chrono::duration_cast<chrono::microseconds>(stop - start).count() << " microseconds\n";
}

void ElipseMidpoint::draw() {
	if (prompting) cout << "Drawing ElipseMidpoint: ";
	if (!a || !b) {
		if (prompting) cout << "invalid input, ";
		return;
	}

	int x = 0;
	int y = b;
	int a2 = a * a;
	int b2 = b * b;
	int p = 4 * b2 - 4 * a2 * b + a2;

	setPixel(xt + x, yt + y);
	setPixel(xt - x, yt + y);
	setPixel(xt + x, yt - y);
	setPixel(xt - x, yt - y);

	while (b2 * x < a2 * y) {
		x += 1;
		if (p < 0) p += 4 * (2 * b2 * x + b2);
		else {
			y -= 1;
			p += 4 * (2 * b2 * x + b2 - 2 * a2 * y);
		}
		setPixel(xt + x, yt + y);
		setPixel(xt - x, yt + y);
		setPixel(xt + x, yt - y);
		setPixel(xt - x, yt - y);
	}
	
	x = a;
	y = 0;
	p = 4 * a2 - 4 * b2 * a + b2;

	setPixel(xt + x, yt + y);
	setPixel(xt - x, yt + y);
	setPixel(xt + x, yt - y);
	setPixel(xt - x, yt - y);

	while (b2 * x >= a2 * y) {
		y += 1;
		if (p < 0) p += 4 * (2 * a2 * y + a2);
		else {
			x -= 1;
			p += 4 * (2 * a2 * y + a2 - 2 * b2 * x);
		}
		setPixel(xt + x, yt + y);
		setPixel(xt - x, yt + y);
		setPixel(xt + x, yt - y);
		setPixel(xt - x, yt - y);
	}

	glFlush();
}

void ElipseMidpoint::drawGL() {
	pixels.clear();
	prompting = false;
	inserting = true;
	this->draw();
	prompting = true;
	inserting = false;
	checking = true;
	auto start = chrono::high_resolution_clock::now();
	float t = 0;
	while (t < 2 * pi) {
		float x = a * cos(t);
		float y = b * sin(t);
		t += 0.001;
		setPixel(round(xt + x), round(yt + y));
	}
	checking = false;
	glFlush();
	auto stop = chrono::high_resolution_clock::now();
	cout << "Drawing EllipseGL: ";
	cout << chrono::duration_cast<chrono::microseconds>(stop - start).count() << " microseconds\n";
}

void ParabolaMidpoint::draw() {
	if (prompting) cout << "Drawing ParabolaMidpoint: ";
	
	if (f == 0) {
		for (int y = 0; y < HEIGHT; ++y) setPixel(xt, y);
		glFlush();
		return;
	}

	int x = 0;
	int y = 0;
	int d = f > 0 ? 1 : -1;
	int a = abs(f);
	int p = 1 - 2 * a;
	
	setPixel(xt + x, yt + y);
	setPixel(xt - x, yt + y);
	while (x < 2 * a) {
		x += 1;
		if (p < 0) p += 2 * x + 1;
		else {
			y += d;
			p += 2 * x + 1 - 4 * a;
		}
		setPixel(xt + x, yt + y);
		setPixel(xt - x, yt + y);
	}

	p = (2 * x + 1) * (2 * x + 1) - 16 * a * (d * y + 1);
	while (yt + y < HEIGHT - 1 && yt + y > 0) {
		y += d;	
		if (p >= 0) p += -16 * a;
		else {
			x += 1;
			p += -16 * a + 8 * x;
		}
		setPixel(xt + x, yt + y);
		setPixel(xt - x, yt + y);
	}

	glFlush();
}

void ParabolaMidpoint::drawGL() {
	pixels.clear();
	prompting = false;
	inserting = true;
	this->draw();
	prompting = true;
	inserting = false;
	checking = true;
	auto start = chrono::high_resolution_clock::now();
	int a = abs(f);
	int d = f > 0 ? 1 : -1;
	float t = -max(sqrt(1.0 * WIDTH / a), HEIGHT / 2.0 / a) - 0.1;
	while (t < WIDTH) {
		float x = d * 2 * a * t;
		float y = d * a * t * t;
		t += 0.001;
		setPixel(round(xt + x), round(yt + y));
	}
	checking = false;
	glFlush();
	auto stop = chrono::high_resolution_clock::now();
	cout << "Drawing ParabolaGL: ";
	cout << chrono::duration_cast<chrono::microseconds>(stop - start).count() << " microseconds\n";
}

void HyperbolaMidpoint::draw() {
	if (prompting) cout << "Drawing HyperbolaMidpoint: ";
	if (!a || !b) {
		if (prompting) cout << "invalid input, ";
		return;
	}
	
	int a2 = a * a;
	int b2 = b * b;
	int x = a;
	int y = 0;
	int p = 4 * a * b2 + b2 - 4 * a2;

	setPixel(xt + x, yt + y);
	setPixel(xt - x, yt + y);
	setPixel(xt + x, yt - y);
	setPixel(xt - x, yt - y);

	while ((yt + y < HEIGHT - 1 || yt - y > 0) && b2 * x >= a2 * y) {
		y += 1;
		if (p >= 0) p += 4 * -a2 * (2 * y + 1);
		else {
			x += 1;
			p += 4 * -a2 * (2 * y + 1) + 8 * b2 * x;
		}
		setPixel(xt + x, yt + y);
		setPixel(xt - x, yt + y);
		setPixel(xt + x, yt - y);
		setPixel(xt - x, yt - y);
	}

	p = 4 * b2 * (x + 1) * (x + 1) - a2 * (2 * y + 1) * (2 * y + 1) - 4 * a2 * b2;
	while (xt + x < WIDTH - 1 || xt - x > 0) {
		x += 1;
		if (p < 0) p += 4 * b2 * (2 * x + 1);
		else {
			y += 1;
			p += 4 * b2 * (2 * x + 1) - 8 * a2 * y;
		}
		setPixel(xt + x, yt + y);
		setPixel(xt - x, yt + y);
		setPixel(xt + x, yt - y);
		setPixel(xt - x, yt - y);
	}

	glFlush();
}

void HyperbolaMidpoint::drawGL() {
	pixels.clear();
	prompting = false;
	inserting = true;
	this->draw();
	prompting = true;
	inserting = false;
	checking = true;
	auto start = chrono::high_resolution_clock::now();
	float t = -pi;
	while (t <= pi) {
		float x = a * 1 / cos(t);
		float y = b * tan(t);
		t += 0.0001;
		setPixel(round(xt + x), round(yt + y));
	}
	checking = false;
	glFlush();
	auto stop = chrono::high_resolution_clock::now();
	cout << "Drawing HyperbolaGL: ";
	cout << chrono::duration_cast<chrono::microseconds>(stop - start).count() << " microseconds\n";
}
