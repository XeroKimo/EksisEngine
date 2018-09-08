#include "EMath.h"
#include"EMathLib.h"
#include <iostream>

bool EMath::SquareToSquareDetection(EVector position1, EVector position2, EVector size1, EVector size2)
{
	int HitDetected = 0;

	float centre1 = position1.x + size1.x / 2;
	float centre2 = position2.x + size2.x / 2;
	float distance = (centre2 - centre1);
	float totalSizeOfHitbox = (size2.x / 2) + (size1.x / 2);
	if (distance * distance <= totalSizeOfHitbox * totalSizeOfHitbox)
	{
		HitDetected++;
	}
	centre1 = position1.y + size1.y / 2;
	centre2 = position2.y + size2.y / 2;
	distance = (centre2 - centre1);
	totalSizeOfHitbox = size1.y / 2 + size2.y / 2;
	if (distance* distance <= totalSizeOfHitbox * totalSizeOfHitbox)
	{
		HitDetected++;
	}
	if (HitDetected == 2)
		return true;
	return false;
}

EVector EMath::CorrectHitBox(EVector position1, EVector position2, EVector size1, EVector size2)
{
	EVector centre1 = position1 + size1 / 2;
	EVector centre2 = position2 + size2 / 2;
	EVector distance = (centre2 - centre1);
	float totalSizeOfHitbox1 = (size2.x / 2) + (size1.x / 2);
	float totalSizeOfHitbox2 = (size2.y / 2) + (size1.y / 2);
	if (distance.x < 0.0f)
		totalSizeOfHitbox1 *= -1;
	if (distance.y < 0.0f)
		totalSizeOfHitbox2 *= -1;
	return EVector(distance.x - totalSizeOfHitbox1, distance.y - totalSizeOfHitbox2);
}









