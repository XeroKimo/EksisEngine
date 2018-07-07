#pragma once
#include "EngineFiles.h"

class Player : public EPhysics
{
public:
	Player();
	~Player();

	void Update(double delta);
	void Render();
	void Input();
	ESquare& GetSquare();

private:
	ESquare m_player;
};