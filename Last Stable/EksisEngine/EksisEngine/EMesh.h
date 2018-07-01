#pragma once
#include "EVector.h"
#include <d3d11.h>

class ColorVector
{
public:
	ColorVector();
	ColorVector(float red, float green, float blue, float alpha = 1.0f);

	float r, g, b, a;
};

class EMesh
{
public:
	EMesh();
	
	bool Initialize(float width, float height);
	void Destroy();
	void Render();
	int GetIndexCount();
private:
	struct VertexType
	{
		EVector position;
		ColorVector color;
	};
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
};