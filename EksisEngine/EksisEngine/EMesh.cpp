#include "EMesh.h"
#include "EksisEngine.h"


EMesh::EMesh()
{
}

bool EMesh::Initialize(float width, float height)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	m_vertexCount = 4;
	m_indexCount = 6;

	vertices = new VertexType[m_vertexCount];
	indices = new unsigned long[m_indexCount];

	vertices[0].position = EVector(0.0f, 0.0f);
	vertices[0].color = ColorVector(1.0f,0.0f,0.0f);

	vertices[1].position = EVector(0.0f, height);
	vertices[1].color = ColorVector(1.0f, 0.0f, 0.0f);

	vertices[2].position = EVector(width, height);
	vertices[2].color = ColorVector(1.0f, 0.0f, 0.0f);

	vertices[3].position = EVector(width,0.0f);
	vertices[3].color = ColorVector(1.0f, 0.0f, 0.0f);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;

	vertexBufferDesc.ByteWidth = sizeof(VertexType)*m_vertexCount;
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	result = EksisEngine::GetInstance()->GetD3DHelper()->GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	indexBufferDesc.ByteWidth = sizeof(unsigned long)*m_indexCount;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	result = EksisEngine::GetInstance()->GetD3DHelper()->GetDevice()->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	delete[] vertices;
	vertices = nullptr;

	delete[] indices;
	indices = nullptr;

	return false;
}

void EMesh::Destroy()
{
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = nullptr;
	}	
	if (m_indexBuffer)
	{	  
		m_indexBuffer->Release();
		m_indexBuffer = nullptr;
	}
}

void EMesh::Render()
{
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(VertexType);
	offset = 0;

	EksisEngine::GetInstance()->GetD3DHelper()->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	EksisEngine::GetInstance()->GetD3DHelper()->GetDeviceContext()->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	EksisEngine::GetInstance()->GetD3DHelper()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

int EMesh::GetIndexCount()
{
	return m_indexCount;
}

ColorVector::ColorVector()
{
	r = g = b = 0.0f;
	a = 1.0f;
}

ColorVector::ColorVector(float red, float green, float blue, float alpha)
{
	r = red;
	g = green;
	b = blue;
	a = alpha;
}
