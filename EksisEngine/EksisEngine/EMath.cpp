#include "EMath.h"
#include"EMathLib.h"
#include <iostream>

int EMath::SquareToSquareDetection(EVector position1, EVector position2, EVector size1, EVector size2)
{
	bool HitDetected = false;

	float centre1 = position1.x + size1.x / 2;
	float centre2 = position2.x + size2.x / 2;
	float distance = (centre2 - centre1);
	float totalSizeOfHitbox = (size2.x/2) + (size1.x / 2);
	if (distance * distance <= totalSizeOfHitbox * totalSizeOfHitbox)
	{
		centre1 = position1.y + size1.y / 2;
		centre2 = position2.y + size2.y / 2;
		distance = (centre2 - centre1);
		totalSizeOfHitbox = size1.y/2 + size2.y/2;
		if (distance* distance <= totalSizeOfHitbox * totalSizeOfHitbox)
		{
			return axisCheck(position1, position2, size1, size2);
			
		}
	}
	return 0;
}

int EMath::axisCheck(EVector position1, EVector position2, EVector size1, EVector size2)
{
	int points[4];
	points[0] = xAxisCheck(position1, position2, size1, size2);
	points[1] = xAxisCheck(position2, position1, size2, size1);
	points[2] = yAxisCheck(position1, position2, size1, size2);
	points[3] = yAxisCheck(position2, position1, size2, size1);
	bool axis = lowestValue(points, 4);
	std::cout << std::endl;
	if (axis == true)
	{/*
		std::cout << (int)distanceY * (int)distanceY << " || " << (int)point1 * (int)point1 << " Y " << std::endl;
		std::cout << (int)distanceY * (int)distanceY << " || " << (int)point2 * (int)point2 << " Y " << std::endl;*/

		return 1;
	}
	else if (axis == false)
	{/*
		std::cout << (int)distanceX * (int)distanceX << " || " << (int)point3 * (int)point3 << " X " << std::endl;
		std::cout << (int)distanceX * (int)distanceX << " || " << (int)point4 * (int)point4 << " X " << std::endl;*/

		return 2;
	}
}

int EMath::xAxisCheck(EVector position1, EVector position2, EVector size1, EVector size2)
{
	float position1Centre = position1.x + size1.x / 2;
	float position2Centre = position2.x + size2.x / 2;
	float line1 = position1Centre + size1.x / 2;
	float line2 = position2Centre - size2.x / 2;
	float pointDistance = line2-line1;
	//std::cout << abs(line1) << "||" << abs(line2) << std::endl;
	//std::cout << distance * distance << " || " << pointDistance *pointDistance << std::endl;
	//std::cout << (int)distance * (int)distance << " || " << (int)pointDistance * (int)pointDistance << std::endl;

	
	return pointDistance;
}

int EMath::yAxisCheck(EVector position1, EVector position2, EVector size1, EVector size2)
{
	float position1Centre = position1.y + size1.y / 2;
	float position2Centre = position2.y + size2.y / 2;
	float line1 = position1Centre + size1.y / 2;
	float line2 = position2Centre - size2.y / 2;
	float pointDistance = line2 - line1;
	//std::cout << abs(line1) << "||" << abs(line2) << std::endl;
	//std::cout <<distance * distance << " || " << pointDistance * pointDistance << std::endl;
	//std::cout << (int)distance * (int)distance << " || " << (int)pointDistance * (int)pointDistance << std::endl;
	return pointDistance;
}

bool EMath::lowestValue(int values[],int size)
{
	int lowestValue = INT_MAX;
	bool axis;
	for (int i = 0; i < size; i++)
	{
		if (values[i] < lowestValue)
		{
			lowestValue = values[i];
			if (i < 2)
			{
				axis = false;
			}
			else
			{
				axis = true;
			}
		}
	}
	return axis;
}

