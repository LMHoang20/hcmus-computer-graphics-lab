#define _USE_MATH_DEFINES
#include "SOIL/SOIL.h"
#include "shape.h"
#include <iostream>
#include <math.h>


Shape::Shape() {
	rotationAxis = { 0, 0, 1 };
	rotationDegree = 0;
	texture[0] = 0;
	translate = { 69, 69, 69 };
	glMode = 69420;
}

void Shape::draw()
{
	glLoadIdentity();
	glTranslatef(translate.x, translate.y, translate.z);
	glRotatef(rotationDegree, rotationAxis.x, rotationAxis.y, rotationAxis.z);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(glMode);
	for (const auto& polygonIndices : indices) {
		for (const auto& vertexIndex : polygonIndices) {
			auto& vertex = vertices[vertexIndex];
			glTexCoord2f(vertex.texture.x, vertex.texture.y);
			glVertex3f(vertex.position.x, vertex.position.y, vertex.position.z);
		}
	}
	glEnd();
}

void Shape::rotate(int degree)
{
	(rotationDegree += degree) %= 360;
}

Shape::~Shape() {
	glDeleteTextures(1, texture);
}

void Shape::loadTexture(const char* filename) {
	texture[0] = SOIL_load_OGL_texture
	(
		filename,
		SOIL_LOAD_RGBA,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
	);
	if (texture[0] == 0) {
		std::cout << "Can't load texture file " << filename << '\n';
	}
	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Shape::cyclicInterleave(std::vector<int>& indices, int num, int startA, int startB)
{
	for (int i = 0; i < num; ++i) {
		indices.push_back(startA + i);
		indices.push_back(startB + i);
	}
	indices.push_back(startA);
	indices.push_back(startB);
}

Cube::Cube(float centerX, float centerY, float centerZ, float sideLength)
{
	float halfLength = sideLength * 0.5;

	vertices = {
		Vertex(Vec(-halfLength, -halfLength, -halfLength), TexCoord(0.0f, 0.0f)),
		Vertex(Vec(-halfLength, -halfLength, +halfLength), TexCoord(0.0f, 1.0f)),
		Vertex(Vec(-halfLength, +halfLength, -halfLength), TexCoord(0.0f, 0.0f)),
		Vertex(Vec(-halfLength, +halfLength, +halfLength), TexCoord(0.0f, 1.0f)),
		Vertex(Vec(+halfLength, -halfLength, -halfLength), TexCoord(1.0f, 0.0f)),
		Vertex(Vec(+halfLength, -halfLength, +halfLength), TexCoord(1.0f, 1.0f)),
		Vertex(Vec(+halfLength, +halfLength, -halfLength), TexCoord(1.0f, 0.0f)),
		Vertex(Vec(+halfLength, +halfLength, +halfLength), TexCoord(1.0f, 1.0f))
	};

	indices = {
		{0, 1, 2},
		{1, 2, 3},
		{4, 5, 6},
		{5, 6, 7},
		{0, 1, 4},
		{1, 4, 5},
		{2, 3, 6},
		{3, 6, 7},
		{0, 2, 4},
		{2, 4, 6},
		{1, 3, 5},
		{3, 5, 7}
	};

	translate = { centerX, centerY, centerZ };
	glMode = GL_TRIANGLES;
	loadTexture("Textures/phandinhtung.bmp");
}

Sphere::Sphere(float centerX, float centerY, float centerZ, float radius, int verticalCount, int horizontalCount )
{
	float verticalStep = 1.0f / (verticalCount - 1);
	float horizontalStep = 1.0f / (horizontalCount - 1);
	float zStep = radius * 2 * verticalStep;
	float aStep = M_PI * 2 * horizontalStep;
	float curZ = -radius;
	for (int i = 0; i < verticalCount; ++i) {
		float radian = 0;
		for (int j = 0; j < horizontalCount; ++j) {
			float r = sqrt(radius * radius - curZ * curZ);
			float curX = r * sin(radian);
			float curY = r * cos(radian);
			vertices.push_back(Vertex(Vec(curX, curY, curZ), TexCoord(horizontalStep * j, verticalStep * i)));
			radian += aStep;
		}
		curZ += zStep;
	}

	for (int i = 0; i + 1 < verticalCount; ++i) {
		indices.emplace_back();
		cyclicInterleave(indices.back(), horizontalCount, i * horizontalCount, (i + 1) * horizontalCount);
	}

	translate = { centerX, centerY, centerZ };
	glMode = GL_TRIANGLE_STRIP;
	loadTexture("Textures/phandinhtung.bmp");
}

Cylinder::Cylinder(float centerX, float centerY, float centerZ, float radius, float height, int horizontalCount)
{
	float horizontalStep = 1.0f / (horizontalCount - 1);
	float aStep = M_PI * 2 * horizontalStep;
	float Z[4] = {-height * 0.5, -height * 0.5, height * 0.5, height * 0.5};
	for (int i = 0; i < 4; ++i) {
		float radian = 0;
		for (int j = 0; j < horizontalCount; ++j) {
			float curX = 0, curY = 0;
			if (i != 0 && i != 3) {
				curX = radius * sin(radian);
				curY = radius * cos(radian);
			}
			float curZ = Z[i];
			vertices.push_back(Vertex(Vec(curX, curY, curZ), TexCoord(horizontalStep * j, i >= 2)));
			radian += aStep;
		}
	}

	for (int i = 0; i + 1 < 4; ++i) {
		indices.emplace_back();
		cyclicInterleave(indices.back(), horizontalCount, i * horizontalCount, (i + 1) * horizontalCount);
	}

	translate = { centerX, centerY, centerZ };
	glMode = GL_TRIANGLE_STRIP;
	loadTexture("Textures/phandinhtung.bmp");
}

Cone::Cone(float centerX, float centerY, float centerZ, float radius, float height, int verticalCount, int horizontalCount)
{
	float verticalStep = 1.0f / (verticalCount - 2);
	float horizontalStep = 1.0f / (horizontalCount - 1);
	float zStep = height * verticalStep;
	float aStep = M_PI * 2 * horizontalStep;
	float curZ = -height * 0.5;
	for (int i = 0; i < verticalCount; ++i) {
		float radian = 0;
		for (int j = 0; j < horizontalCount; ++j) {
			float r = 0;
			if (i != 0) {
				r = radius * (height * 0.5 - curZ) / height;
			}
			float curX = r * sin(radian);
			float curY = r * cos(radian);
			vertices.push_back(Vertex(Vec(curX, curY, curZ), TexCoord(horizontalStep * j, verticalStep * i)));
			radian += aStep;
		}
		if (i != 0) {
			curZ += zStep;
		}
	}

	for (int i = 0; i + 1 < verticalCount; ++i) {
		indices.emplace_back();
		cyclicInterleave(indices.back(), horizontalCount, i * horizontalCount, (i + 1) * horizontalCount);
	}

	translate = { centerX, centerY, centerZ };
	glMode = GL_TRIANGLE_STRIP;
	loadTexture("Textures/phandinhtung.bmp");
}

Torus::Torus(float centerX, float centerY, float centerZ, float majorRadius, float minorRadius, int verticalCount, int horizontalCount)
{
	float verticalStep = 1.0f / (verticalCount - 1);
	float horizontalStep = 1.0f / (horizontalCount - 1);
	float majorAStep = M_PI * 2 * horizontalStep;
	float minorAStep = M_PI * 2 * verticalStep;
	float minorRadian = 0;
	for (int i = 0; i < verticalCount; ++i) {
		float MR = majorRadius + minorRadius * sin(minorRadian);
		float curZ = -minorRadius * cos(minorRadian);
		float majorRadian = 0;
		for (int j = 0; j < horizontalCount; ++j) {
			float curX = MR * sin(majorRadian);
			float curY = MR * cos(majorRadian);
			vertices.push_back(Vertex(Vec(curX, curY, curZ), TexCoord(horizontalStep * j, verticalStep * i)));
			majorRadian += majorAStep;
		}
		minorRadian += minorAStep;
	}
	for (int i = 0; i + 1 < verticalCount; ++i) {
		indices.emplace_back();
		cyclicInterleave(indices.back(), horizontalCount, i * horizontalCount, (i + 1) * horizontalCount);
	}

	translate = { centerX, centerY, centerZ };
	glMode = GL_TRIANGLE_STRIP;
	loadTexture("Textures/phandinhtung.bmp");
}

Hyperboloid::Hyperboloid(float centerX, float centerY, float centerZ, float a, float b, float height, int verticalCount, int horizontalCount)
{
	float verticalStep = 1.0f / (verticalCount - 3);
	float horizontalStep = 1.0f / (horizontalCount - 1);
	float zStep = height * verticalStep;
	float aStep = M_PI * 2 * horizontalStep;
	float curZ = -height * 0.5;
	for (int i = 0; i < verticalCount; ++i) {
		float radian = 0;
		for (int j = 0; j < horizontalCount; ++j) {
			float r = 0;
			if (i != 0 && i != verticalCount - 1) {
				r = a * sqrt((curZ * curZ) / (b * b) + 1);
			}
			float curX = r * sin(radian);
			float curY = r * cos(radian);
			vertices.push_back(Vertex(Vec(curX, curY, curZ), TexCoord(horizontalStep * j, verticalStep * i)));
			radian += aStep;
		}
		if (i != 0 && i != verticalCount - 2) {
			curZ += zStep;
		}
	}

	for (int i = 0; i + 1 < verticalCount; ++i) {
		indices.emplace_back();
		cyclicInterleave(indices.back(), horizontalCount, i * horizontalCount, (i + 1) * horizontalCount);
	}

	translate = { centerX, centerY, centerZ };
	glMode = GL_TRIANGLE_STRIP;
	loadTexture("Textures/phandinhtung.bmp");
}

Paraboloid::Paraboloid(float centerX, float centerY, float centerZ, float a, float height, int verticalCount, int horizontalCount) {
	float verticalStep = 1.0f / (verticalCount - 2);
	float horizontalStep = 1.0f / (horizontalCount - 1);
	float zStep = height * verticalStep;
	float aStep = M_PI * 2 * horizontalStep;
	float curZ = -height * 0.5;
	for (int i = 0; i < verticalCount; ++i) {
		float radian = 0;
		for (int j = 0; j < horizontalCount; ++j) {
			float r = 0;
			if (i != 0) {
				r = sqrt(std::max(0.0f, (height * 0.5f - curZ) / a));
			}
			float curX = r * sin(radian);
			float curY = r * cos(radian);
			vertices.push_back(Vertex(Vec(curX, curY, curZ), TexCoord(horizontalStep * j, verticalStep * i)));
			radian += aStep;
		}
		if (i != 0) {
			curZ += zStep;
		}
	}

	for (int i = 0; i + 1 < verticalCount; ++i) {
		indices.emplace_back();
		cyclicInterleave(indices.back(), horizontalCount, i * horizontalCount, (i + 1) * horizontalCount);
	}

	translate = { centerX, centerY, centerZ };
	glMode = GL_TRIANGLE_STRIP;
	loadTexture("Textures/phandinhtung.bmp");
}