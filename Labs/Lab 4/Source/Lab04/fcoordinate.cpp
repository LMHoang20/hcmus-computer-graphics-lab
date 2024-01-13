#include "fcoordinate.h"
#include "constants.h"
#include <cmath>

fCoordinate::fCoordinate(float _x, float _y) : x{ _x }, y{ _y } { };

fCoordinate fCoordinate::operator+(fCoordinate other) const
{
	return fCoordinate(x + other.x, y + other.y);
}
fCoordinate fCoordinate::operator-(fCoordinate other) const
{
	return fCoordinate(x - other.x, y - other.y);
}
fCoordinate fCoordinate::operator*(float scalar) const
{
	return fCoordinate(x * scalar, y * scalar);
}
fCoordinate fCoordinate::operator+=(fCoordinate other)
{
	return fCoordinate(x += other.x, y += other.y);
}
fCoordinate fCoordinate::operator-=(fCoordinate other)
{
	return fCoordinate(x -= other.x, y -= other.y);
}
fCoordinate fCoordinate::operator*=(float scalar)
{
	return fCoordinate(x *= scalar, y *= scalar);
}
bool fCoordinate::operator==(fCoordinate other)
{
	return x == other.x && y == other.y;
}
fCoordinate fCoordinate::translate(fCoordinate dir)
{
	return *this += dir;
}
fCoordinate fCoordinate::rotate(fCoordinate pivot, float degree)
{
	fCoordinate tmp = *this - pivot;
	float radian = degree * PI / 180;
	tmp.x = tmp.x * std::cos(radian) - tmp.y * std::sin(radian);
	tmp.y = tmp.x * std::sin(radian) + tmp.y * std::cos(radian);
	return (*this = tmp + pivot);
}
fCoordinate fCoordinate::scale(fCoordinate pivot, float scaleFactorX, float scaleFactorY)
{
	fCoordinate tmp = *this - pivot;
	tmp.x *= scaleFactorX;
	tmp.y *= scaleFactorY;
	return (*this = tmp + pivot);
}
std::pair<fCoordinate, fCoordinate> makeSquareBound(fCoordinate bound1, fCoordinate bound2)
{	
	fCoordinate center = (bound1 + bound2) * 0.5;
	fCoordinate dir = (bound1 - bound2) * 0.5;
	if (abs(dir.x) > abs(dir.y)) dir.x = dir.y;
	else dir.y = dir.x;
	return std::pair<fCoordinate, fCoordinate>(center + dir, center - dir);
}
