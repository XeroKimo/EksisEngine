#include "EShader.h"
#include "EksisEngine.h"

EShader::EShader()
{
}

bool EShader::Initialize(HWND hWnd, const wchar_t * vsFile, const wchar_t * psFile)
{
	HRESULT result;
	ID3D10Blob* errorMessage;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	unsigned int numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;
	D3D11_SAMPLER_DESC samplerDesc;

	errorMessage = nullptr;
	vertexShaderBuffer = nullptr;
	pixelShaderBuffer = nullptr;
	
	result = D3DCompileFromFile(vsFile, NULL, NULL, "ColorVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &vertexShaderBuffer, &errorMessage);
	if (FAILED(result))
	{
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hWnd, vsFile);
		}

		else
		{
			MessageBox(hWnd, vsFile, L"Missing Shader File", MB_OK);
		}
		return false;
	}

	result = D3DCompileFromFile(psFile, NULL, NULL, "ColorPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
		&pixelShaderBuffer, &errorMessage);
	if (FAILED(result))
	{
		// If the shader failed to compile it should have writen something to the error message.
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hWnd, psFile);
		}
		// If there was nothing in the error message then it simply could not find the file itself.
		else
		{
			MessageBox(hWnd, psFile, L"Missing Shader File", MB_OK);
		}

		return false;
	}
	result = EksisEngine::GetInstance()->GetD3DHelper()->GetDevice()->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(),vertexShaderBuffer->GetBufferSize(),NULL, &m_vertexShader);
	if (FAILED(result))
	{
		return false;
	}

	result = EksisEngine::GetInstance()->GetD3DHelper()->GetDevice()->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
	if (FAILED(result))
	{
		return false;
	}

	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	//polygonLayout[1].SemanticName = "COLOR";
	//polygonLayout[1].SemanticIndex = 0;
	//polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	//polygonLayout[1].InputSlot = 0;
	//polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	//polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	//polygonLayout[1].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "TEXCOORD";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	result = EksisEngine::GetInstance()->GetD3DHelper()->GetDevice()->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_layout);
	if (FAILED(result))
	{
		return false;
	}

	vertexShaderBuffer->Release();
	vertexShaderBuffer = nullptr;

	pixelShaderBuffer->Release();
	pixelShaderBuffer = nullptr;

	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	result = EksisEngine::GetInstance()->GetD3DHelper()->GetDevice()->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
	if (FAILED(result))
	{
		return false;
	}

	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// Create the texture sampler state.
	result = EksisEngine::GetInstance()->GetD3DHelper()->GetDevice()->CreateSamplerState(&samplerDesc, &m_sampleState);
	if (FAILED(result))
	{
		return false;
	}
	m_renderMatrix = new MatrixBufferType;
	return true;
}

void EShader::Shutdown()
{
	if (m_matrixBuffer)
	{	 
		m_matrixBuffer->Release();
		m_matrixBuffer = nullptr;
	}

	// Release the layout.
	if (m_layout)
	{	 
		m_layout->Release();
		m_layout = nullptr;
	}

	// Release the pixel shader.
	if (m_pixelShader)
	{	 
		m_pixelShader->Release();
		m_pixelShader = nullptr;
	}

	// Release the vertex shader.
	if (m_vertexShader)
	{	
		m_vertexShader->Release();
		m_vertexShader = nullptr;
	}
}

void EShader::Render(int indexCount, ID3D11ShaderResourceView* texture)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	unsigned int bufferNumber;

	result = EksisEngine::GetInstance()->GetD3DHelper()->GetDeviceContext()->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	dataPtr = (MatrixBufferType*)mappedResource.pData;
	dataPtr->model = m_renderMatrix->model;
	dataPtr->view = m_renderMatrix->view;
	dataPtr->ortho = m_renderMatrix->ortho;

	EksisEngine::GetInstance()->GetD3DHelper()->GetDeviceContext()->Unmap(m_matrixBuffer, 0);

	bufferNumber = 0;
	EksisEngine::GetInstance()->GetD3DHelper()->GetDeviceContext()->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);
	EksisEngine::GetInstance()->GetD3DHelper()->GetDeviceContext()->PSSetShaderResources(0, 1, &texture);

	EksisEngine::GetInstance()->GetD3DHelper()->GetDeviceContext()->IASetInputLayout(m_layout);
	EksisEngine::GetInstance()->GetD3DHelper()->GetDeviceContext()->VSSetShader(m_vertexShader, NULL, 0);
	EksisEngine::GetInstance()->GetD3DHelper()->GetDeviceContext()->PSSetShader(m_pixelShader, NULL, 0);

	EksisEngine::GetInstance()->GetD3DHelper()->GetDeviceContext()->DrawIndexed(indexCount, 0, 0);


}

void EShader::SetModel(EMatrix m)
{
	m_renderMatrix->model = m;
}

void EShader::SetView(EMatrix v)
{
	m_renderMatrix->view = v;
}

void EShader::SetOrtho(EMatrix o)
{
	m_renderMatrix->ortho = o;
}

void EShader::OutputShaderErrorMessage(ID3D10Blob * errorMessage, HWND hWnd, const wchar_t* shaderFileName)
{
	char* compileErrors;
	unsigned long long bufferSize, i;
	std::ofstream fout;


	// Get a pointer to the error message text buffer.
	compileErrors = (char*)(errorMessage->GetBufferPointer());

	// Get the length of the message.
	bufferSize = errorMessage->GetBufferSize();

	// Open a file to write the error message to.
	fout.open("shader-error.txt");
	// Write out the error message.
	for (i = 0; i<bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	// Close the file.
	fout.close();

	// Release the error message.
	errorMessage->Release();
	errorMessage = 0;

	// Pop a message up on the screen to notify the user to check the text file for compile errors.
	MessageBox(hWnd, L"Error compiling shader.  Check shader-error.txt for message.", shaderFileName, MB_OK);

	return;
}
