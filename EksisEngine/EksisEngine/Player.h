#pragma once
#include "EngineFiles.h"

class Player : public EPhysics
{
public:
	Player();
	~Player();

	void Update(double delta);
	void Render();
	void Input(EInput* input);
	ESquare& GetSquare();
	void SetPosition(EVector position);

private:
	ESquare m_player;
	EVector m_velocity;
	float m_maxSpeed;

private:
	void MovePlayer(double delta);
};