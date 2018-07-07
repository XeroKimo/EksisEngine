#pragma once

#include "EMatrix.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <fstream>

class EShader 
{
	struct MatrixBufferType
	{
		EMatrix model;
		EMatrix view;
		EMatrix ortho;
	};
public:
	EShader();
	bool Initialize(HWND hWnd, const wchar_t* vsFile, const wchar_t* psFile);
	void Shutdown();
	void Render(int indexCount, ID3D11ShaderResourceView* texture);

	
	void SetModel(EMatrix m);
	void SetView(EMatrix v);
	void SetOrtho(EMatrix o);

private:
	void OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hWnd, const wchar_t* shaderFileName);

private:
	MatrixBufferType * m_renderMatrix;
	ID3D11VertexShader * m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;
	D3D11_MAPPED_SUBRESOURCE m_mappedResource;
	ID3D11SamplerState* m_sampleState;
};