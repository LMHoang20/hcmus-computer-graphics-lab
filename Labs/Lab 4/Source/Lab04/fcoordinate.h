#pragma once
#include <utility>

class fCoordinate {
public:
	float x;
	float y;
	fCoordinate(float _x, float _y);
	fCoordinate operator+(fCoordinate other) const;
	fCoordinate operator-(fCoordinate other) const;
	fCoordinate operator*(float scalar) const;
	fCoordinate operator+=(fCoordinate other);
	fCoordinate operator-=(fCoordinate other);
	fCoordinate operator*=(float scalar);
	bool operator==(fCoordinate other);
	fCoordinate translate(fCoordinate dir);
	fCoordinate rotate(fCoordinate pivot, float degree);
	fCoordinate scale(fCoordinate pivot, float scaleFactorX, float scaleFactorY);
	friend std::pair<fCoordinate, fCoordinate> makeSquareBound(fCoordinate bound1, fCoordinate bound2);
};

#pragma once
