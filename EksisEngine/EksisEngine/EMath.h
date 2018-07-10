#pragma once
#include "EVector.h"
#include "EMatrix.h"


struct EMath
{
	static int SquareToSquareDetection(EVector position1, EVector position2, EVector size1, EVector size2);

private:
	static int axisCheck(EVector position1, EVector position2, EVector size1, EVector size2);
	static int xAxisCheck(EVector position1, EVector position2, EVector size1, EVector size2);
	static int yAxisCheck(EVector position1, EVector position2, EVector size1, EVector size2);
	static bool lowestValue(int values[], int size);
};