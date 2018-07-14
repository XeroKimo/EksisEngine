#pragma once
#include "EngineFiles.h"

class Box : public EPhysics
{
public:
	Box();
	~Box();

	void Update(double delta);
	void Render();

	void SetPosition(EVector position);

private:
	ESquare m_box;
	float m_maxSpeed;
};