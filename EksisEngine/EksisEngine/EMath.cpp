#include "EMath.h"
#include"EMathLib.h"
#include <iostream>

int EMath::SquareToSquareDetection(EVector position1, EVector position2, EVector size1, EVector size2)
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
		return axisCheck(position1, position2, size1, size2);
	return 0;
}

float EMath::CorrectHitBox(EVector position1, EVector position2, EVector size1, EVector size2)
{
	int points[4];
	points[0] = xAxisCheck(position1, position2, size1, size2);	//Right check, all relative to position 1
	points[1] = xAxisCheck(position2, position1, size2, size1);	//left check
	points[2] = yAxisCheck(position1, position2, size1, size2);	//top check
	points[3] = yAxisCheck(position2, position1, size2, size1); //bot check
	return points[lowestValue(points, 4) - 1];
}










int EMath::axisCheck(EVector position1, EVector position2, EVector size1, EVector size2)
{
	int points[4];
	points[0] = xAxisCheck(position1, position2, size1, size2);	//right check, all relative to position 1
	points[1] = xAxisCheck(position2, position1, size2, size1);	//left check
	points[2] = yAxisCheck(position1, position2, size1, size2);	//top check
	points[3] = yAxisCheck(position2, position1, size2, size1);	//bottom check
	//std::cout << std::endl;
	return lowestValue(points, 4);
}

float EMath::xAxisCheck(EVector position1, EVector position2, EVector size1, EVector size2)
{
	float position1Centre = position1.x + size1.x / 2;
	float position2Centre = position2.x + size2.x / 2;
	float line1 = position1Centre + size1.x / 2;
	float line2 = position2Centre - size2.x / 2;
	float pointDistance = line2-line1;
	//std::cout << abs(pointDistance) << " X " << std::endl;
	return abs(pointDistance);
}

float EMath::yAxisCheck(EVector position1, EVector position2, EVector size1, EVector size2)
{
	float position1Centre = position1.y + size1.y / 2;
	float position2Centre = position2.y + size2.y / 2;
	float line1 = position1Centre + size1.y / 2;
	float line2 = position2Centre - size2.y / 2;
	float pointDistance = line2 - line1;
	//std::cout << abs(pointDistance) << " Y " << std::endl;
	return abs(pointDistance);
}

int EMath::lowestValue(int values[],int size)
{
	int lowestValue = INT_MAX;
	int lowestPoint;
	for (int i = 0; i < size; i++)
	{
		//std::cout << values[i] << " | ";
		if (values[i] < lowestValue)
		{
			lowestValue = values[i];
			lowestPoint = i + 1;
		}
	}
	//std::cout <<"\n"<< lowestPoint << "\n";
	return lowestPoint;
}

