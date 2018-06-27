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

EVector::~EVector()
{
}
