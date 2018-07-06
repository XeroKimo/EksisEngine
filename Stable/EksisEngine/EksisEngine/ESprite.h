#pragma once
#include "EMesh.h"
#include "ERenderable.h"
#include "ETexture.h"

class ESprite : public ERenderable
{
public:
	ESprite();
	ESprite(const wchar_t* imageFile);
	~ESprite();

	bool SetTexture(const wchar_t* imageFile);
	void Shutdown();

	virtual void Render();
private:
	ETexture * m_texture;
	EMesh * m_mesh;
};