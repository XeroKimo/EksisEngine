#pragma once
#include <d3d11.h>
#include <dxgi.h>

class EDirectXHelper
{
public:
	EDirectXHelper();

	virtual bool Initialize(int ClientWidth, int ClientHeight, HWND WindowHandle);
	virtual void Shutdown();

	virtual void BeginRender(float R = 0.0f, float G = 0.0f, float B = 0.0f, float A = 1.0f) = 0;
	virtual void EndRender();

	void ChangeResolution(int NewWidth, int NewHeight);
	void SetFullscreen(bool Fullscreen);
	void ChangeFramerate(int FPS);
	void SetVSyncEnabled(bool Enabled);
	void SetFPSCapEnabled(bool Enabled);

	ID3D11Device* GetDevice() const;
	ID3D11DeviceContext* GetDeviceContext() const;

protected:
	virtual void ClearRenderTarget();
	virtual void CreateRenderTarget(int Width, int Height) = 0;

protected:
	ID3D11Device * m_device;
	ID3D11DeviceContext* m_deviceContext;
	IDXGISwapChain* m_swapChain;

	bool m_VSyncEnabled;
	bool m_FPSCapEnabled;
	int m_FPSLimit;
};