#pragma once
class EVector 
{
public:
	EVector();
	EVector(float zx, float zy);
	friend EVector operator+(const EVector& first ,const EVector& second);
	EVector operator-(const EVector other);
	EVector operator+=(const EVector other);
	EVector operator*=(const EVector other);
	EVector operator*(const EVector other);
	EVector operator*(const float other);
	EVector operator/(const EVector other);
	EVector operator/(const float other);
	bool operator!= (const EVector other);
	bool operator== (const EVector other);

	~EVector();

	float x;
	float y;
	float z;
	
};