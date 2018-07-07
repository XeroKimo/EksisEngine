#pragma once
#include "ERenderable.h"

class EMesh;

class ESquare : public ERenderable
{
public:
	ESquare(float width =64.0f, float height = 64.0f);
	~ESquare();

	void Load();
	void Unload();
	virtual void Render();

	void SetColor(float r, float g, float b, float a = 1.0f);
	void SetDimensions(float width, float height);
	void SetDimensions(EVector dimensions);


private:
	EMesh * m_mesh;
	bool m_display;
	float m_red, m_green, m_blue, m_alpha;
};