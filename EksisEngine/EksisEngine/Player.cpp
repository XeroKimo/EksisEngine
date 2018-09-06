#include "Player.h"
#include <iostream>

Player::Player()
{
	SetFlag(COLLIDABLE|GRAVITY|MOVEABLE);
	//SetFlag(COLLIDABLE);
	SetTag(TAG_PLAYER);

	m_player.SetColor(0.0f, 0.0f, 1.0f);
	m_player.SetDimensions(64.0f, 128.0f);
	m_player.SetOrigin(0.5f, 0.5f);
	SetHitboxOffset(EVector(-m_player.GetDimension().x * m_player.GetOrigin().x, -m_player.GetDimension().y * m_player.GetOrigin().y));
	SetHitbox(m_player.GetDimension());
	m_maxSpeed = 300.0f;
}

Player::~Player()
{
}

void Player::Update(double delta)
{
	m_player.SetPosition(GetHitboxPosition());
	EVector currentPos = m_player.GetPosition() - GetHitboxOffset();
	MovePlayer(delta);
	p_totalVelocity =  p_velocity + p_instantVelocity;
	p_instantVelocity = p_instantVelocity * EVector(0.95, 0.95);
	if (p_instantVelocity.x < 0.0001)
	{
		p_instantVelocity.x = 0;
	}
	if (p_instantVelocity.y < 0.0001)
	{
		p_instantVelocity.y = 0;
	}
	currentPos += p_totalVelocity;
	m_player.SetPosition(currentPos);
	SetHitboxPosition(currentPos + GetHitboxOffset());
	//std::cout << currentPos.x << " || " << currentPos.y << " player " << std::endl;
	std::cout << p_totalVelocity.x << " || " <<p_totalVelocity.y << " player " << std::endl;
	//std::cout << GetHitboxPosition().x << " || " << GetHitboxPosition().y << std::endl;
	//if (!p_inAir)
	//{
	//		p_velocity = EVector(p_velocity.x*0.95, p_velocity.y);
	//}

}

void Player::Render()
{
	m_player.Render();
}

void Player::Input(EInput* input)
{

}

ESquare& Player::GetSquare()
{
	return m_player;
}

void Player::SetPosition(EVector position)
{
	m_player.SetPosition(position);
	SetHitboxPosition(position);
}

void Player::MovePlayer(double delta)
{
	if (IsKeyDown(EKeyCode::D) || IsKeyHeld(EKeyCode::D))
	{
		p_velocity = EVector(m_maxSpeed * delta, p_velocity.y);
	}
	if (IsKeyDown(EKeyCode::A) || IsKeyHeld(EKeyCode::A))
	{
		p_velocity = EVector(-m_maxSpeed * delta, p_velocity.y);
	}
	if (IsKeyInactive(EKeyCode::D) && IsKeyInactive(EKeyCode::A))
	{
		p_velocity = EVector(0.0f, p_velocity.y);
	}
	if (IsKeyDown(EKeyCode::W) || IsKeyHeld(EKeyCode::W))
	{
		if (!p_inAir)
		{
			SetVelocity(p_velocity.x, 1000.0f*delta);
			p_inAir = true;
		}
	}
}
