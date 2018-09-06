#pragma once
#include "EngineFiles.h"

class Platform : public EPhysics
{
public:
	Platform();
	~Platform();

	void Update(double delta);
	void Render();
	void Input(EInput* input);
	ESquare& GetSquare();

private:
	ESquare m_platform;
};