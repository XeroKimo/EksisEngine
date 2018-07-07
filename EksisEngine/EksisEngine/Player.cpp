#include "Player.h"

Player::Player()
{
	SetFlag(GRAVITY);
	m_player.SetColor(0.0f, 0.0f, 1.0f);
}

Player::~Player()
{
}

void Player::Update(double delta)
{
	p_velocity += EVector(p_acceleration.x*delta, p_acceleration.y*delta);
	//p_velocity += p_acceleration;
	EVector currentPos = m_player.GetPosition();
	//EVector newPos = EVector(currentPos.x + p_velocity.x, currentPos.y + p_velocity.y);
	currentPos += p_velocity;
	m_player.SetPosition(currentPos);
}

void Player::Render()
{
	m_player.Render();
}

void Player::Input()
{
}

ESquare& Player::GetSquare()
{
	return m_player;
}
