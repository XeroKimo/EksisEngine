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
	void Render();


private:
	EMesh * m_mesh;
	bool m_display;
};