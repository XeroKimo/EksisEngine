#include "ED3DHelper.h"

ED3DHelper::ED3DHelper()
	: m_renderTargetView(nullptr)
	, m_depthStencilView(nullptr)
	, m_depthEnabledStencilState(nullptr)
	, m_depthDisabledStencilState(nullptr)
	, m_solidRasterizerState(nullptr)
	, m_wireframeRasterizerState(nullptr)
{
}

bool ED3DHelper::Initialize(int ClientWidth, int ClientHeight, HWND WindowHandle)
{
	if (!__super::Initialize(ClientWidth, ClientHeight, WindowHandle))
	{
		return false;
	}

	CreateRenderTarget(ClientWidth, ClientHeight);

	D3D11_DEPTH_STENCIL_DESC DepthEnabledStencilStateDesc;
	DepthEnabledStencilStateDesc.DepthEnable = true;
	DepthEnabledStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	DepthEnabledStencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS;
	DepthEnabledStencilStateDesc.StencilEnable = true;
	DepthEnabledStencilStateDesc.StencilReadMask = 0xFF;
	DepthEnabledStencilStateDesc.StencilWriteMask = 0xFF;
	DepthEnabledStencilStateDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	DepthEnabledStencilStateDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	DepthEnabledStencilStateDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	DepthEnabledStencilStateDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	DepthEnabledStencilStateDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	DepthEnabledStencilStateDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	DepthEnabledStencilStateDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	DepthEnabledStencilStateDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	if (FAILED(m_device->CreateDepthStencilState(&DepthEnabledStencilStateDesc, &m_depthEnabledStencilState)))
	{
		MessageBox(NULL, L"Failed to create depth enabled stencil state.", L"ED3DHelper", MB_OK);
		return false;
	}

	D3D11_DEPTH_STENCIL_DESC DepthDisabledStencilStateDesc;
	DepthDisabledStencilStateDesc.DepthEnable = false;
	DepthDisabledStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	DepthDisabledStencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS;
	DepthDisabledStencilStateDesc.StencilEnable = true;
	DepthDisabledStencilStateDesc.StencilReadMask = 0xFF;
	DepthDisabledStencilStateDesc.StencilWriteMask = 0xFF;
	DepthDisabledStencilStateDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	DepthDisabledStencilStateDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	DepthDisabledStencilStateDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	DepthDisabledStencilStateDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	DepthDisabledStencilStateDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	DepthDisabledStencilStateDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	DepthDisabledStencilStateDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	DepthDisabledStencilStateDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	if (FAILED(m_device->CreateDepthStencilState(&DepthDisabledStencilStateDesc, &m_depthDisabledStencilState)))
	{
		MessageBox(NULL, L"Failed to create depth disabled stencil state.", L"ED3DHelper", MB_OK);
		return false;
	}

	m_deviceContext->OMSetDepthStencilState(m_depthEnabledStencilState, 1);

	D3D11_RASTERIZER_DESC SolidRasterizerDesc;
	SolidRasterizerDesc.AntialiasedLineEnable = false;
	SolidRasterizerDesc.CullMode = D3D11_CULL_BACK;
	SolidRasterizerDesc.DepthBias = NULL;
	SolidRasterizerDesc.DepthBiasClamp = 0.0f;
	SolidRasterizerDesc.DepthClipEnable = true;
	SolidRasterizerDesc.FillMode = D3D11_FILL_SOLID;
	SolidRasterizerDesc.FrontCounterClockwise = false;
	SolidRasterizerDesc.MultisampleEnable = false;
	SolidRasterizerDesc.ScissorEnable = false;
	SolidRasterizerDesc.SlopeScaledDepthBias = 0.0f;

	if (FAILED(m_device->CreateRasterizerState(&SolidRasterizerDesc, &m_solidRasterizerState)))
	{
		MessageBox(NULL, L"Failed to create solid rasterizer state.", L"ED3DHelper", MB_OK);
		return false;
	}

	D3D11_RASTERIZER_DESC WireframeRasterizerDesc;
	WireframeRasterizerDesc.AntialiasedLineEnable = false;
	WireframeRasterizerDesc.CullMode = D3D11_CULL_BACK;
	WireframeRasterizerDesc.DepthBias = NULL;
	WireframeRasterizerDesc.DepthBiasClamp = 0.0f;
	WireframeRasterizerDesc.DepthClipEnable = true;
	WireframeRasterizerDesc.FillMode = D3D11_FILL_SOLID;
	WireframeRasterizerDesc.FrontCounterClockwise = false;
	WireframeRasterizerDesc.MultisampleEnable = false;
	WireframeRasterizerDesc.ScissorEnable = false;
	WireframeRasterizerDesc.SlopeScaledDepthBias = 0.0f;

	if (FAILED(m_device->CreateRasterizerState(&WireframeRasterizerDesc, &m_wireframeRasterizerState)))
	{
		MessageBox(NULL, L"Failed to create wireframe rasterizer state.", L"ED3DHelper", MB_OK);
		return false;
	}

	m_deviceContext->RSSetState(m_solidRasterizerState);

	return true;
}

void ED3DHelper::Shutdown()
{
	if (m_wireframeRasterizerState)
	{
		m_wireframeRasterizerState->Release();
		m_wireframeRasterizerState = nullptr;
	}

	if (m_solidRasterizerState)
	{
		m_solidRasterizerState->Release();
		m_solidRasterizerState = nullptr;
	}

	if (m_depthDisabledStencilState)
	{
		m_depthDisabledStencilState->Release();
		m_depthDisabledStencilState = nullptr;
	}

	if (m_depthEnabledStencilState)
	{
		m_depthEnabledStencilState->Release();
		m_depthEnabledStencilState = nullptr;
	}

	ClearRenderTarget();

	__super::Shutdown();
}

void ED3DHelper::BeginRender(float R, float G, float B, float A)
{
	float Colour[] = { R, G, B, A };
	m_deviceContext->ClearRenderTargetView(m_renderTargetView, Colour);
	m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH |D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void ED3DHelper::EnableDepth()
{
	m_deviceContext->OMSetDepthStencilState(m_depthEnabledStencilState, 1);
}

void ED3DHelper::DisableDepth()
{
	m_deviceContext->OMSetDepthStencilState(m_depthDisabledStencilState, 1);
}

void ED3DHelper::EnableWireframe()
{
	m_deviceContext->RSSetState(m_wireframeRasterizerState);
}

void ED3DHelper::DisableWireframe()
{
	m_deviceContext->RSSetState(m_solidRasterizerState);
}

void ED3DHelper::ClearRenderTarget()
{
	__super::ClearRenderTarget();

	if (m_renderTargetView)
	{
		m_renderTargetView->Release();
		m_renderTargetView = nullptr;
	}

	if (m_depthStencilView)
	{
		m_depthStencilView->Release();
		m_depthStencilView = nullptr;
	}
}

void ED3DHelper::CreateRenderTarget(int Width, int Height)
{
	ID3D11Texture2D* RenderBackBuffer;
	if (FAILED(m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&RenderBackBuffer)))
	{
		MessageBox(NULL, L"Failed to get back buffer of swap chain.", L"ED3DHelper", MB_OK);
		return;
	}
	if (FAILED(m_device->CreateRenderTargetView(RenderBackBuffer, NULL, &m_renderTargetView)))
	{
		MessageBox(NULL, L"Failed to create render target view.", L"ED3DHelper", MB_OK);
		if (RenderBackBuffer)
		{
			RenderBackBuffer->Release();
			RenderBackBuffer = nullptr;
		}
		return;
	}
	if (RenderBackBuffer)
	{
		RenderBackBuffer->Release();
		RenderBackBuffer = nullptr;
	}

	D3D11_TEXTURE2D_DESC DepthBufferDesc;
	DepthBufferDesc.Width = Width;
	DepthBufferDesc.Height = Height;
	DepthBufferDesc.MipLevels = 1;
	DepthBufferDesc.ArraySize = 1;
	DepthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	DepthBufferDesc.SampleDesc.Count = 1;
	DepthBufferDesc.SampleDesc.Quality = 0;
	DepthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	DepthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	DepthBufferDesc.CPUAccessFlags = NULL;
	DepthBufferDesc.MiscFlags = NULL;

	ID3D11Texture2D* DepthStencilBuffer;
	if (FAILED(m_device->CreateTexture2D(&DepthBufferDesc, NULL, &DepthStencilBuffer)))
	{
		MessageBox(NULL, L"Failed to create depth stencil buffer", L"ED3DHelper", MB_OK);
		return;
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC DepthStencilViewDesc;
	ZeroMemory(&DepthStencilViewDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	DepthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	DepthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	DepthStencilViewDesc.Texture2D.MipSlice = NULL;

	if (FAILED(m_device->CreateDepthStencilView(DepthStencilBuffer, &DepthStencilViewDesc, &m_depthStencilView)))
	{
		MessageBox(NULL, L"Failed to create depth stencil view", L"ED3DHelper", MB_OK);
		if (DepthStencilBuffer)
		{
			DepthStencilBuffer->Release();
			DepthStencilBuffer = nullptr;
		}
		return;
	}

	if (DepthStencilBuffer)
	{
		DepthStencilBuffer->Release();
		DepthStencilBuffer = nullptr;
	}

	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

	D3D11_VIEWPORT Viewport;
	Viewport.TopLeftX = 0.0f;
	Viewport.TopLeftY = 0.0f;
	Viewport.Width = (float)Width;
	Viewport.Height = (float)Height;
	Viewport.MinDepth = 0.0f;
	Viewport.MaxDepth = 1.0f;

	m_deviceContext->RSSetViewports(1, &Viewport);

	return;
}
