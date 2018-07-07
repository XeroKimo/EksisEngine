#include "EMatrix.h"
#include <Math.h>

EMatrix::EMatrix()
{
	m_matrix[0][0] = 1; m_matrix[0][1] = 0; m_matrix[0][2] = 0; m_matrix[0][3] = 0;
	m_matrix[1][0] = 0; m_matrix[1][1] = 1; m_matrix[1][2] = 0; m_matrix[1][3] = 0;
	m_matrix[2][0] = 0; m_matrix[2][1] = 0; m_matrix[2][2] = 1; m_matrix[2][3] = 0;
	m_matrix[3][0] = 0; m_matrix[3][1] = 0; m_matrix[3][2] = 0; m_matrix[3][3] = 1;
}


EMatrix EMatrix::operator=(EMatrix m)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_matrix[i][j] = m.m_matrix[i][j];
		}
	}
	return *this;
}

EMatrix EMatrix::operator*(EMatrix m)
{
	EMatrix mat;
	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat.m_matrix[i][j] = m_matrix[i][0] * m.m_matrix[0][j] + m_matrix[i][1] * m.m_matrix[1][j] + m_matrix[i][2] * m.m_matrix[2][j] + m_matrix[i][3] * m.m_matrix[3][j];
		}
	}
	return mat;



}

void EMatrix::Transpose()
{
	float oldMatrix[4][4];
	oldMatrix[0][0] = m_matrix[0][0]; oldMatrix[0][1] = m_matrix[0][1]; oldMatrix[0][2] = m_matrix[0][2]; oldMatrix[0][3] = m_matrix[0][3];
	oldMatrix[1][0] = m_matrix[1][0]; oldMatrix[1][1] = m_matrix[1][1]; oldMatrix[1][2] = m_matrix[1][2]; oldMatrix[1][3] = m_matrix[1][3];
	oldMatrix[2][0] = m_matrix[2][0]; oldMatrix[2][1] = m_matrix[2][1]; oldMatrix[2][2] = m_matrix[2][2]; oldMatrix[2][3] = m_matrix[2][3];
	oldMatrix[3][0] = m_matrix[3][0]; oldMatrix[3][1] = m_matrix[3][1]; oldMatrix[3][2] = m_matrix[3][2]; oldMatrix[3][3] = m_matrix[3][3];

	m_matrix[0][0] = oldMatrix[0][0]; m_matrix[0][1] = oldMatrix[1][0]; m_matrix[0][2] = oldMatrix[2][0]; m_matrix[0][3] = oldMatrix[3][0];
	m_matrix[1][0] = oldMatrix[0][1]; m_matrix[1][1] = oldMatrix[1][1]; m_matrix[1][2] = oldMatrix[2][1]; m_matrix[1][3] = oldMatrix[3][1];
	m_matrix[2][0] = oldMatrix[0][2]; m_matrix[2][1] = oldMatrix[1][2]; m_matrix[2][2] = oldMatrix[2][2]; m_matrix[2][3] = oldMatrix[3][2];
	m_matrix[3][0] = oldMatrix[0][3]; m_matrix[3][1] = oldMatrix[1][3]; m_matrix[3][2] = oldMatrix[2][3]; m_matrix[3][3] = oldMatrix[3][3];
}

EMatrix EMatrix::Identity()
{
	EMatrix matrix;
	matrix.SetIdentity();
	return matrix;
}

EMatrix EMatrix::Ortho(float left, float right, float bottom, float top)
{
	EMatrix ortho;
	ortho.SetOrtho(left,right,bottom,top);
	return ortho;
}

void EMatrix::SetOrtho(float left, float right, float bottom, float top)
{
	m_matrix[0][0] = 2 / (right - left); m_matrix[0][3] = -(right + left) / (right - left);
	m_matrix[1][1] = 2 / (top - bottom); m_matrix[1][3] = -(top + bottom) / (top - bottom);
	m_matrix[2][2] = 1.0f; m_matrix[2][3] = 0.0f;
}

void EMatrix::SetIdentity()
{
	m_matrix[0][0] = 1; m_matrix[0][1] = 0; m_matrix[0][2] = 0; m_matrix[0][3] = 0;
	m_matrix[1][0] = 0; m_matrix[1][1] = 1; m_matrix[1][2] = 0; m_matrix[1][3] = 0;
	m_matrix[2][0] = 0; m_matrix[2][1] = 0; m_matrix[2][2] = 1; m_matrix[2][3] = 0;
	m_matrix[3][0] = 0; m_matrix[3][1] = 0; m_matrix[3][2] = 0; m_matrix[3][3] = 1;
}

void EMatrix::SetPosition(EVector position)
{
	m_matrix[0][3] = position.x;
	m_matrix[1][3] = position.y;
	m_matrix[2][3] = position.z;
}

void EMatrix::SetRotation(float radians)
{
	m_matrix[0][0] = cos(radians); m_matrix[0][1] = -sin(radians);
	m_matrix[1][0] = sin(radians); m_matrix[1][1] = cos(radians);
}

void EMatrix::SetScale(float scale)
{
	m_matrix[0][0] *= scale;
	m_matrix[1][1] *= scale;
	m_matrix[2][2] *= scale;
}


