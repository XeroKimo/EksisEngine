#pragma once
#include "ETexture.h"
#include <map>
#include <d3d11.h>

class ETextureManager
{
public:
	ETextureManager();
	
	bool Initialize();
	void Shutdown();
	void Load(const wchar_t* imageFile);
	void Unload(const wchar_t* imageFile);
	ETexture* GetTexture(const wchar_t* imageFile);
	ID3D11ShaderResourceView* BlankTexture();
private:
	std::map<const wchar_t, ETexture> m_textureMap;
};