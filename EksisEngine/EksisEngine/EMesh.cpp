#include "EMesh.h"
#include "EksisEngine.h"


EMesh::EMesh():
	m_vertices(nullptr)
{
}

bool EMesh::Initialize(float width, float height)
{
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	m_vertexCount = 4;
	m_indexCount = 6;

	m_vertices = new VertexType[m_vertexCount];
	indices = new unsigned long[m_indexCount];

	m_vertices[0].position = EVector(0.0f, 0.0f);
	m_vertices[0].tex = TexVector(0.0f, 1.0f);
	m_vertices[0].color = ColorVector(1.0f,1.0f,1.0f);

	m_vertices[1].position = EVector(0.0f, height);
	m_vertices[1].tex = TexVector(0.0f, 0.0f);
	m_vertices[1].color = ColorVector(1.0f, 1.0f, 1.0f);
	
	m_vertices[2].position = EVector(width, height);
	m_vertices[2].tex = TexVector(1.0f, 0.0f);
	m_vertices[2].color = ColorVector(1.0f, 1.0f, 1.0f);
	
	m_vertices[3].position = EVector(width,0.0f);
	m_vertices[3].tex = TexVector(1.0f, 1.0f);
	m_vertices[3].color = ColorVector(1.0f, 1.0f, 1.0f);

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

	vertexData.pSysMem = m_vertices;
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

	delete[] indices;
	indices = nullptr;

	return true;
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

void EMesh::SetDimensions(float width, float height)
{
	D3D11_BUFFER_DESC vertexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData;

	m_vertices[0].position = EVector(0.0f, 0.0f);
	m_vertices[1].position = EVector(0.0f, height);
	m_vertices[2].position = EVector(width, height);
	m_vertices[3].position = EVector(width, 0.0f);

	vertexBufferDesc.ByteWidth = sizeof(VertexType)*m_vertexCount;
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = m_vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	EksisEngine::GetInstance()->GetD3DHelper()->GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
}

void EMesh::SetColor(float red, float green,float blue, float alpha)
{
	D3D11_BUFFER_DESC vertexBufferDesc; 
	D3D11_SUBRESOURCE_DATA vertexData;
	ColorVector rgb(red, green, blue,alpha);
	

	m_vertices[0].color = rgb;
	m_vertices[1].color = rgb;
	m_vertices[2].color = rgb;
	m_vertices[3].color = rgb;
	
	vertexBufferDesc.ByteWidth = sizeof(VertexType)*m_vertexCount;
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = m_vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	EksisEngine::GetInstance()->GetD3DHelper()->GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
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

TexVector::TexVector()
{
	u = v = 0.0f;
}

TexVector::TexVector(float r, float g)
{
	u = r;
	v = g;
}
