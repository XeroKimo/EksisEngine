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
class TexVector
{
public:
	TexVector();
	TexVector(float r, float g);

	float u, v;
};

class EMesh
{
public:
	EMesh();
	
	bool Initialize(float width, float height);
	void Destroy();
	void Render();
	void SetColor(float red, float green, float blue, float alpha = 1.0f);
	int GetIndexCount();
private:
	struct VertexType
	{
		EVector position;
		TexVector tex;
		//ColorVector color;
	};
	VertexType* m_vertices;
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	bool m_texture;
};