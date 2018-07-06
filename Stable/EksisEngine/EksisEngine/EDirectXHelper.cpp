#include "EDirectXHelper.h"

EDirectXHelper::EDirectXHelper()
	: m_deviceContext(nullptr)
	, m_swapChain(nullptr)
	, m_VSyncEnabled(false)
	, m_FPSCapEnabled(false)
	, m_FPSLimit(0)
	, m_device(nullptr)
{
}

bool EDirectXHelper::Initialize(int ClientWidth, int ClientHeight, HWND WindowHandle)
{
	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	if (m_VSyncEnabled)
	{
		SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}
	else if (m_FPSCapEnabled)
	{
		SwapChainDesc.BufferDesc.RefreshRate.Numerator = m_FPSLimit;
		SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}
	else
	{
		SwapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}
	SwapChainDesc.BufferDesc.Width = ClientWidth;
	SwapChainDesc.BufferDesc.Height = ClientHeight;
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.BufferCount = 1;
	SwapChainDesc.OutputWindow = WindowHandle;
	SwapChainDesc.SampleDesc.Count = 1;
	SwapChainDesc.SampleDesc.Quality = 0;
	SwapChainDesc.Windowed = true;
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	SwapChainDesc.Flags = NULL;

	D3D_FEATURE_LEVEL Levels[] = { D3D_FEATURE_LEVEL_11_0 };
	D3D_FEATURE_LEVEL AcceptedLevel;
	HRESULT result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_BGRA_SUPPORT, Levels, 1, D3D11_SDK_VERSION, &SwapChainDesc, &m_swapChain, &m_device, &AcceptedLevel, &m_deviceContext);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Failed to create device and swap chain.", L"EDirectXHelper", MB_OK);
		return false;
	}

	return true;
}

void EDirectXHelper::Shutdown()
{
	if (m_swapChain)
	{
		m_swapChain->Release();
		m_swapChain = nullptr;
	}

	if (m_deviceContext)
	{
		m_deviceContext->Release();
		m_deviceContext = nullptr;
	}

	if (m_device)
	{
		m_device->Release();
		m_device = nullptr;
	}
}

void EDirectXHelper::EndRender()
{
	if (m_VSyncEnabled)
	{
		m_swapChain->Present(1, NULL);
	}
	else
	{
		m_swapChain->Present(0, NULL);
	}
}

void EDirectXHelper::ChangeResolution(int NewWidth, int NewHeight)
{
	ClearRenderTarget();

	m_deviceContext->ClearState();

	if (FAILED(m_swapChain->ResizeBuffers(0, NewWidth, NewHeight, DXGI_FORMAT_UNKNOWN, NULL)))
	{
		MessageBox(NULL, L"Failed to change resolution of swap chain. Potentially unreleased render target.", L"EDirectXHelper", MB_OK);
	}

	CreateRenderTarget(NewWidth, NewHeight);
}

void EDirectXHelper::SetFullscreen(bool Fullscreen)
{
	if (FAILED(m_swapChain->SetFullscreenState(Fullscreen, NULL)))
	{
		MessageBox(NULL, L"Failed to change fullscreen state.", L"EDirectXHelper", MB_OK);
	}
}

void EDirectXHelper::ChangeFramerate(int FPS)
{
	m_FPSLimit = FPS;

	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	if (FAILED(m_swapChain->GetDesc(&SwapChainDesc)))
	{
		MessageBox(NULL, L"Failed to get swap chain description", L"EDirectXHelper", MB_OK);
	}

	DXGI_MODE_DESC NewMode;
	NewMode.Width = SwapChainDesc.BufferDesc.Width;
	NewMode.Height = SwapChainDesc.BufferDesc.Height;
	NewMode.Format = SwapChainDesc.BufferDesc.Format;
	NewMode.ScanlineOrdering = SwapChainDesc.BufferDesc.ScanlineOrdering;
	NewMode.Scaling = SwapChainDesc.BufferDesc.Scaling;
	NewMode.RefreshRate.Denominator = 1;

	if (m_VSyncEnabled)
	{
		NewMode.RefreshRate.Numerator = 60;
	}
	else if (m_FPSCapEnabled)
	{
		NewMode.RefreshRate.Numerator = m_FPSLimit;
	}
	else
	{
		NewMode.RefreshRate.Numerator = 0;
	}

	if (FAILED(m_swapChain->ResizeTarget(&NewMode)))
	{
		MessageBox(NULL, L"Failed to change FPS limit on swap chain.", L"UDirectXHelper", MB_OK);
	}
}

void EDirectXHelper::SetVSyncEnabled(bool Enabled)
{
	m_VSyncEnabled = Enabled;
	ChangeFramerate(m_FPSLimit);
}

void EDirectXHelper::SetFPSCapEnabled(bool Enabled)
{
	m_FPSCapEnabled = Enabled;
	ChangeFramerate(m_FPSLimit);
}

ID3D11Device * EDirectXHelper::GetDevice() const
{
	return m_device;
}

ID3D11DeviceContext * EDirectXHelper::GetDeviceContext() const
{
	return m_deviceContext;
}

void EDirectXHelper::ClearRenderTarget()
{
}
