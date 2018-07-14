#pragma once
#include "EVector.h"
#include "EMatrix.h"


struct EMath
{
	static int SquareToSquareDetection(EVector position1, EVector position2, EVector size1, EVector size2);
	static float CorrectHitBox(EVector position1, EVector position2, EVector size1, EVector size2);
	static float xAxisCheck(EVector position1, EVector position2, EVector size1, EVector size2);
	static float yAxisCheck(EVector position1, EVector position2, EVector size1, EVector size2);

private:
	static int axisCheck(EVector position1, EVector position2, EVector size1, EVector size2);
	static int lowestValue(int values[], int size);
};