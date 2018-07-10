#include "EVector.h"

EVector::EVector()
{
	EVector::x = 0;
	EVector::y = 0;
	EVector::z = 0;
}

EVector::EVector(float zx, float zy)
{
	x = zx;
	y = zy;
	z = 0.0f;
}

EVector EVector::operator+(const EVector other)
{
	x += other.x;
	y += other.y;
	return EVector(x,y);
}

EVector EVector::operator-(const EVector other)
{
	x -= other.x;
	y -= other.y;
	return EVector(x, y);
}
EVector EVector::operator+=(const EVector other)
{
	x += other.x;
	y += other.y;
	return EVector(x, y);
}

EVector EVector::operator*(const EVector other)
{
	x *= other.x;
	y *= other.y;
	return EVector(x, y);
}
EVector EVector::operator/(const EVector other)
{
	x /= other.x;
	y /= other.y;
	return EVector(x, y);
}
EVector EVector::operator/(const float other)
{
	x /= other;
	y /= other;
	return EVector(x, y);
}
EVector::~EVector()
{
}
