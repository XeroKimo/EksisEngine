#pragma once
#include "EVector.h"

class EMatrix
{
public:
	EMatrix();
	EMatrix operator=(EMatrix m);
	EMatrix operator*(EMatrix m);
	void Transpose();

	static EMatrix Identity();
	static EMatrix Ortho(float left, float right, float bottom, float top);
	void SetOrtho(float left, float right, float bottom, float top);
	void SetIdentity();

	void SetPosition(EVector position);
	void SetRotation(float radians);
	void SetScale(EVector scale);

	float m_matrix[4][4];
};