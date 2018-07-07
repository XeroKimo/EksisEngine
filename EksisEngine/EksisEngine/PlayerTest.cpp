#include "PlayerTest.h"

Player::Player()
{
	player.SetColor(0.0f, 0.0f, 1.0f);
}

void Player::Update(double delta)
{
}

void Player::Render()
{
	player.Render();
}

void Player::Input()
{
}

void Player::SetID(int id)
{
}

ESquare& Player::GetSquare()
{
	return player;
}
