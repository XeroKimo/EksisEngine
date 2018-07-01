#pragma once
#include <d3d11.h>
#include <stdio.h>
#include<wincodec.h>

struct WICTranslate
{
	WICPixelFormatGUID                wic;
	DXGI_FORMAT         format;
};

static WICTranslate g_WICFormats[] =
{
	{ GUID_WICPixelFormat128bppRGBAFloat,       DXGI_FORMAT_R32G32B32A32_FLOAT },

	{ GUID_WICPixelFormat64bppRGBAHalf,         DXGI_FORMAT_R16G16B16A16_FLOAT },
	{ GUID_WICPixelFormat64bppRGBA,             DXGI_FORMAT_R16G16B16A16_UNORM },

	{ GUID_WICPixelFormat32bppRGBA,             DXGI_FORMAT_R8G8B8A8_UNORM },
	{ GUID_WICPixelFormat32bppBGRA,             DXGI_FORMAT_B8G8R8A8_UNORM }, // DXGI 1.1
	{ GUID_WICPixelFormat32bppBGR,              DXGI_FORMAT_B8G8R8X8_UNORM }, // DXGI 1.1

	{ GUID_WICPixelFormat32bppRGBA1010102XR,    DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM }, // DXGI 1.1
	{ GUID_WICPixelFormat32bppRGBA1010102,      DXGI_FORMAT_R10G10B10A2_UNORM },
	{ GUID_WICPixelFormat32bppRGBE,             DXGI_FORMAT_R9G9B9E5_SHAREDEXP }
};

class ETexture
{
public:
	ETexture();

	bool Initialize(const wchar_t* fileName);
	void Shutdown();
	ID3D11ShaderResourceView* GetTexture();

	int GetDXGIFormatBitsPerPixel(DXGI_FORMAT& dxgiFormat);

	UINT GetHeight();
	UINT GetWidth();
private:
	//bool LoadFile(const wchar_t* fileName);
private:

	ID3D11Texture2D* m_texture;
	ID3D11ShaderResourceView* m_textureView;
	UINT m_textureHeight, m_textureWidth;

	
};