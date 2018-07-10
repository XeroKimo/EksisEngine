#pragma once
class EVector 
{
public:
	EVector();
	EVector(float zx, float zy);
	EVector operator+(const EVector other);
	EVector operator-(const EVector other);
	EVector operator+=(const EVector other);
	EVector operator*(const EVector other);
	EVector operator/(const EVector other);
	EVector operator/(const float  other);
	~EVector();

	float x;
	float y;
	float z;
	
};