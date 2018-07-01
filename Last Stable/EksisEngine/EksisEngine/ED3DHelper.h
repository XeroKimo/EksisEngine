#pragma once
#include "EDirectXHelper.h"

class ED3DHelper : public EDirectXHelper
{
public:
	ED3DHelper(); 
	virtual bool Initialize(int ClientWidth, int ClientHeight, HWND WindowHandle) override;
	virtual void Shutdown() override;

	virtual void BeginRender(float R = 0.0f, float G = 0.0f, float B = 0.0f, float A = 1.0f) override;

	void EnableDepth();
	void DisableDepth();

	void EnableWireframe();
	void DisableWireframe();

protected:
	virtual void ClearRenderTarget() override;
	virtual void CreateRenderTarget(int Width, int Height) override;

protected:
	ID3D11RenderTargetView * m_renderTargetView;
	ID3D11DepthStencilView* m_depthStencilView;

	ID3D11DepthStencilState* m_depthEnabledStencilState;
	ID3D11DepthStencilState* m_depthDisabledStencilState;

	ID3D11RasterizerState* m_solidRasterizerState;
	ID3D11RasterizerState* m_wireframeRasterizerState;
};