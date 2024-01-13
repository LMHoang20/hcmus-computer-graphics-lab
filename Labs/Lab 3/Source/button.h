#pragma once
#include <GL/glut.h>
#include <string>

using namespace std;

class Button {
	int left, bottom, right, top;
	string text;
public:
	Button(int _left, int _bottom, int _right, int _top, string _text);
	void draw();
	bool collision(int x, int y);
};