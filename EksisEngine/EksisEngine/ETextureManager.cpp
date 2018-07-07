#include "ETextureManager.h"

using namespace std;
ETextureManager::ETextureManager() 
{
}

bool ETextureManager::Initialize()
{
	Load(L"White.png");
	return true;
}

void ETextureManager::Shutdown()
{
	for (pair<const wchar_t, ETexture> test : m_textureMap)
	{
		wchar_t string = test.first;
		m_textureMap[test.first].Shutdown();
	}
	m_textureMap.clear();
}

void ETextureManager::Load(const wchar_t* imageFile)
{
	ETexture texture;
	if (texture.Initialize(imageFile))
	{
		m_textureMap[*imageFile] = texture;
	}
}

void ETextureManager::Unload(const wchar_t * imageFile)
{
	m_textureMap[*imageFile].Shutdown();
	m_textureMap.erase(*imageFile);
}

ETexture * ETextureManager::GetTexture(const wchar_t * imageFile)
{
	for (const auto pair : m_textureMap)
	{
		if (pair.first == *imageFile)
		{
			return &m_textureMap[*imageFile];
		}
	}
	return &m_textureMap[*L"White.png"];
}

ID3D11ShaderResourceView* ETextureManager::BlankTexture()
{
	return m_textureMap[*L"White.png"].GetTexture();
}
