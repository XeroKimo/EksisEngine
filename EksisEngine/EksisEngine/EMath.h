#pragma once
#include "EVector.h"
#include "EMatrix.h"


struct EMath
{
	static bool SquareToSquareDetection(EVector position1, EVector position2, EVector size1, EVector size2);
	static EVector CorrectHitBox(EVector position1, EVector position2, EVector size1, EVector size2);
};