#pragma once
#include "GL/glut.h"
#include <vector>

class Shape {
protected:
	struct Vec {
		float x, y, z;
		Vec() : x(), y(), z() { };
		Vec(float _x, float _y, float _z) : x(_x), y(_y), z(_z) { };
	};
	struct TexCoord {
		float x, y;
		TexCoord() : x(), y() { };
		TexCoord(float _x, float _y) : x(_x), y(_y) { };
	};
	struct Vertex {
		Vec position;
		TexCoord texture;
		Vertex() { };
		Vertex(Vec _position, TexCoord _texture) : position(_position), texture(_texture) { };
	};

	GLuint texture[1];
	Vec translate;
	Vec rotationAxis;
	int rotationDegree;

	std::vector < Vertex > vertices;
	std::vector < std::vector < int > > indices;
	GLenum glMode;

	Shape();
	void loadTexture(const char* filename);
	void cyclicInterleave(std::vector < int >& indices, int num, int startA, int startB);
public:
	void draw();
	void rotate(int degree);
	virtual ~Shape();
};

class Cube : public Shape {
public:
	Cube(float centerX, float centerY, float centerZ, float sideLength);
};

class Sphere : public Shape {
public:
	Sphere(float centerX, float centerY, float centerZ, float radius, int verticalCount, int horizontalCount);
};

class Cylinder : public Shape {
public:
	Cylinder(float centerX, float centerY, float centerZ, float radius, float height, int horizontalCount);
};

class Cone : public Shape {
public:
	Cone(float centerX, float centerY, float centerZ, float radius, float height, int verticalCount, int horizontalCount);
};

class Torus : public Shape {
public:
	Torus(float centerX, float centerY, float centerZ, float majorRadius, float minorRadius, int verticalCount, int horizontalCount);
};

class Hyperboloid : public Shape {
public:
	Hyperboloid(float centerX, float centerY, float centerZ, float a, float b, float height, int verticalCount, int horizontalCount);
};

class Paraboloid : public Shape {
public:
	Paraboloid(float centerX, float centerY, float centerZ, float a, float height, int verticalCount, int horizontalCount);
};