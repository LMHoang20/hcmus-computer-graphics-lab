#pragma once
#include <GL/glut.h>
#include "application.h"
#include "shape.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <chrono>
#include <random>

using namespace std;

App::App(int _height, int _width, const char* _filename) : height(_height), width(_width) {
	getShapesFromFile(_filename);
}

App::~App() {
	clearShapes();
}

void App::clearShapes() {
	if (shapes.empty()) return;
	for (int i = 0; i < shapes.size(); ++i) delete shapes[i];
	shapes.clear();
}

void App::drawShapes() {
	glFlush();
	for (auto& shape : shapes) {
		glColor3ub(rand() % 256, rand() % 256, rand() % 256);
		shape->draw();
	}
}

void App::drawShape(int x) {
	if (x < 0 || x >= shapes.size()) return;
	glColor3ub(0, 0, 0);
	shapes[x]->draw();
}

void App::checkCurrentShape() {
	if (shapes.empty()) return;
	shapes[currentShape]->drawGL();
}

void App::drawCurrentShape() {
	drawShape(currentShape);
}

bool App::changeImage(int x) {
	if (x < 0 || x >= shapes.size()) return false;
	currentShape = x;
	return true;
}

bool App::leftImage() {
	return changeImage(currentShape - 1);
}

bool App::rightImage() {
	return changeImage(currentShape + 1);
}

void App::getShapesFromFile(const char* filename) {
	clearShapes();
	ifstream ifs(filename);
	if (!ifs.is_open()) {
		cout << "Can't find input.txt\n";
		return;
	}
	while (true) {
		vector < int > input;
		int type, a, b, c, d;
		ifs >> type >> a >> b >> c;
		if (!ifs.good()) break;
		input.push_back(type);
		input.push_back(a);
		input.push_back(b);
		input.push_back(c);
		if (type != 2 && type != 4) {
			ifs >> d;
			input.push_back(d);
		}
		Shape* shape = App::createShape(input);
		shapes.push_back(shape);
	}
	ifs.close();
}

void App::clearWindows() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(2.0);
	glFlush();
}

Shape* App::createShape(vector < int > input) {
	Shape* result = nullptr;
	switch (input[0]) {
	case 0:
		result = new LineDDA(RGBColor(255,255,255), input[1], input[2], input[3], input[4]);
		cout << "Create LineDDA " << input[1] << ' ' << input[2] << ' ' << input[3] << ' ' << input[4] << '\n';
		break;
	case 1:
		result = new LineBresenham(RGBColor(255, 255, 255), input[1], input[2], input[3], input[4]);
		cout << "Create LineBresenham " << input[1] << ' ' << input[2] << ' ' << input[3] << ' ' << input[4] << '\n';
		break;
	case 2:
		result = new CircleMidpoint(RGBColor(255, 255, 255), input[1], input[2], input[3]);
		cout << "Create CircleMidpoint " << input[1] << ' ' << input[2] << ' ' << input[3] << '\n';
		break;
	case 3:
		result = new ElipseMidpoint(RGBColor(255, 255, 255), input[1], input[2], input[3], input[4]);
		cout << "Create ElipseMidpoint " << input[1] << ' ' << input[2] << ' ' << input[3] << ' ' << input[4] << '\n';
		break;
	case 4:
		result = new ParabolaMidpoint(RGBColor(255, 255, 255), input[1], input[2], input[3]);
		cout << "Create ParabolaMidpoint " << input[1] << ' ' << input[2] << ' ' << input[3] << '\n';
		break;
	case 5:
		result = new HyperbolaMidpoint(RGBColor(255, 255, 255), input[1], input[2], input[3], input[4]);
		cout << "Create LineDDA " << input[1] << ' ' << input[2] << ' ' << input[3] << ' ' << input[4] << '\n';
		break;
	default:
		cout << "WTF\n";
	}
	return result;
}
