#include "ETexture.h"
#include "EksisEngine.h"


ETexture::ETexture():
	m_texture(nullptr),
	m_textureView(nullptr)
{
}

bool ETexture::Initialize(const wchar_t * fileName)
{
	ID3D11Device* device = EksisEngine::GetInstance()->GetD3DHelper()->GetDevice();
	ID3D11DeviceContext* context = EksisEngine::GetInstance()->GetD3DHelper()->GetDeviceContext();

	D3D11_TEXTURE2D_DESC textureDesc;
	HRESULT hResult;
	unsigned int rowPitch;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;

	IWICImagingFactory *wicFactory = nullptr;
	CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&wicFactory);

	IWICBitmapDecoder *wicDecoder = nullptr;

	hResult = wicFactory->CreateDecoderFromFilename(fileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &wicDecoder);
	if (FAILED(hResult))
	{
		return false;
	}

	IWICBitmapFrameDecode* wicFrame = nullptr;
	hResult = wicDecoder->GetFrame(0, &wicFrame);
	if (FAILED(hResult))
	{
		return false;
	}

	wicFrame->GetSize(&m_textureWidth, &m_textureHeight);

	WICPixelFormatGUID wicFormat;
	hResult=wicFrame->GetPixelFormat(&wicFormat);
	if (FAILED(hResult))
	{
		return false;
	}

	DXGI_FORMAT dxFormat;
	for (int i = 0; i < 9; i++)
	{
		if (wicFormat == g_WICFormats[i].wic)
		{
			dxFormat = g_WICFormats[i].format;
			i = 9;
		}
		if (i == 8 && dxFormat!=g_WICFormats[8].format)
		{
			dxFormat = DXGI_FORMAT_UNKNOWN;
		}
	}

	int bitsPerPixel = GetDXGIFormatBitsPerPixel(dxFormat);
	int bytesPerRow = (m_textureWidth * bitsPerPixel) / 8; // number of bytes in each row of the image data
	int imageSize = bytesPerRow * m_textureHeight; // total image size in bytes

												 // allocate enough memory for the raw image data, and set imageData to point to that memory
	BYTE *imageData = (BYTE*)malloc(imageSize);
	wicFrame->CopyPixels(NULL, bytesPerRow, imageSize, imageData);



	///*result = LoadFile(fileName, height, width)
	//if (!result)
	//{
	//return false;
	//}*/
	//
	textureDesc.Height = m_textureHeight;
	textureDesc.Width = m_textureWidth;
	textureDesc.MipLevels = 0;
	textureDesc.ArraySize = 1;
	textureDesc.Format = dxFormat;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;


	hResult = device->CreateTexture2D(&textureDesc, NULL, &m_texture);
	if (FAILED(hResult))
	{
		return false;
	}

	rowPitch = (m_textureWidth * 4) * sizeof(unsigned char);
	context->UpdateSubresource(m_texture, 0, NULL, imageData, bytesPerRow, 0);

	srvDesc.Format = textureDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = -1;

	hResult = device->CreateShaderResourceView(m_texture, &srvDesc, &m_textureView);
	if (FAILED(hResult))
	{
		return false;
	}

	context->GenerateMips(m_textureView);

	return true;

}

void ETexture::Shutdown()
{
	if (m_texture)
	{
		delete m_texture;
		m_texture = nullptr;
	}
	if (m_textureView)
	{
		delete m_textureView;
		m_textureView = nullptr;
	}
}

ID3D11ShaderResourceView * ETexture::GetTexture()
{
	return m_textureView;
}

int ETexture::GetDXGIFormatBitsPerPixel(DXGI_FORMAT & dxgiFormat)
{
	if (dxgiFormat == DXGI_FORMAT_R32G32B32A32_FLOAT) return 128;
	else if (dxgiFormat == DXGI_FORMAT_R16G16B16A16_FLOAT) return 64;
	else if (dxgiFormat == DXGI_FORMAT_R16G16B16A16_UNORM) return 64;
	else if (dxgiFormat == DXGI_FORMAT_R8G8B8A8_UNORM) return 32;
	else if (dxgiFormat == DXGI_FORMAT_B8G8R8A8_UNORM) return 32;
	else if (dxgiFormat == DXGI_FORMAT_B8G8R8X8_UNORM) return 32;
	else if (dxgiFormat == DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM) return 32;

	else if (dxgiFormat == DXGI_FORMAT_R10G10B10A2_UNORM) return 32;
	else if (dxgiFormat == DXGI_FORMAT_B5G5R5A1_UNORM) return 16;
	else if (dxgiFormat == DXGI_FORMAT_B5G6R5_UNORM) return 16;
	else if (dxgiFormat == DXGI_FORMAT_R32_FLOAT) return 32;
	else if (dxgiFormat == DXGI_FORMAT_R16_FLOAT) return 16;
	else if (dxgiFormat == DXGI_FORMAT_R16_UNORM) return 16;
	else if (dxgiFormat == DXGI_FORMAT_R8_UNORM) return 8;
	else if (dxgiFormat == DXGI_FORMAT_A8_UNORM) return 8;
}

UINT ETexture::GetHeight()
{
	return m_textureHeight;
}

UINT ETexture::GetWidth()
{
	return m_textureWidth;
}
