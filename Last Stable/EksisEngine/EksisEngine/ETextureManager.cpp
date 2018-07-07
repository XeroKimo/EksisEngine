#include "ETextureManager.h"

using namespace std;
ETextureManager::ETextureManager() 
{
}

bool ETextureManager::Initialize()
{
	return true;
}

void ETextureManager::Shutdown()
{
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
	m_textureMap.erase(*imageFile);
}

ETexture * ETextureManager::GetTexture(const wchar_t * imageFile)
{
	return &m_textureMap[*imageFile];
}
