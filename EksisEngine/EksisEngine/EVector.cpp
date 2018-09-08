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





EVector EVector::operator-(const EVector other)
{
	EVector result;
	result.x = x - other.x;
	result.y = y - other.y;
	result.z = z - other.z;
	return result;
}
EVector EVector::operator+=(const EVector other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

EVector EVector::operator*=(const EVector other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return *this;
}

EVector EVector::operator*(const EVector other)
{
	EVector result;
	result.x = x * other.x;
	result.y = y * other.y;
	result.z = z * other.z;
	return result;
}
EVector EVector::operator*(const float other)
{
	EVector result;
	result.x = x * other;
	result.y = y * other;
	result.z = z * other;
	return result;
}
EVector EVector::operator/(const EVector other)
{
	EVector result;
	result.x = x / other.x;
	result.y = y / other.y;
	result.z = z / other.z;
	return result;
}
EVector EVector::operator/(const float other)
{
	EVector result;
	result.x = x / other;
	result.y = y / other;
	result.z = z / other;
	return result;
}
bool EVector::operator!=(const EVector other)
{
	if (x != other.x
		|| y != other.y
		|| z != other.z)
	{
		return true;
	}
	return false;
}
bool EVector::operator==(const EVector other)
{
	if (x == other.x
		&& y == other.y
		&& z == other.z)
		return true;
	return false;
}
EVector::~EVector()
{
}

EVector operator+(const EVector & first, const EVector & second)
{
	return EVector(first.x + second.x, first.y + second.y);
}
