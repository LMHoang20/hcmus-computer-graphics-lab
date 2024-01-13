#pragma once
#include <GL/glut.h>
#include <vector>
#include "shape.h"

using namespace std;

class App {
	int height;
	int width;
	vector<Shape*> shapes;
	int currentShape = 0;
	bool changeImage(int x);
public:
	App(int _height, int _width, const char* _filename);

	void getShapesFromFile(const char* filename);
	void clearShapes();
	void drawShapes();
	void drawShape(int x);
	void checkCurrentShape();
	void drawCurrentShape();
	bool leftImage();
	bool rightImage();
	void clearWindows();
	Shape* createShape(vector<int> input);

	~App();
};