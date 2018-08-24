#include "Box.h"

Box::Box()
{
	SetFlag(COLLIDABLE | MOVEABLE | GRAVITY );
	m_box.SetColor(0.0f, 1.0f, 0.0f);
	//m_box.SetOrigin(0.5f, 0.5f);
	SetHitboxOffset(EVector(-m_box.GetDimension().x * m_box.GetOrigin().x, -m_box.GetDimension().y * m_box.GetOrigin().y));
	SetHitbox(m_box.GetDimension());
}

Box::~Box()
{
}

void Box::Update(double delta)
{
	m_box.SetPosition(GetHitboxPosition());
	EVector currentPos = m_box.GetPosition() - GetHitboxOffset();
	p_totalVelocity = p_velocity+p_instantVelocity;
	p_instantVelocity = p_instantVelocity * EVector(0.95, 0.95);
	if (p_instantVelocity.x < 0.0001 && p_instantVelocity.x > -0.0001)
	{
		p_instantVelocity.x = 0;
	}
	if (p_instantVelocity.y < 0.0001 && p_instantVelocity.y > -0.0001)
	{
		p_instantVelocity.y = 0;
	}
	currentPos += p_totalVelocity;
	m_box.SetPosition(currentPos);
	SetHitboxPosition(currentPos + GetHitboxOffset());
	std::cout << p_instantVelocity.x << " || " << p_instantVelocity.y << std::endl;
	/*std::cout << currentPos.x << " || " << currentPos.y << " Box" << std::endl;
	std::cout << GetHitboxPosition().x << " || " << GetHitboxPosition().y << std::endl;*/
	if (!p_inAir)
	p_velocity = EVector(0.0f, 0.0f);
}

void Box::Render()
{
	m_box.Render();
}

void Box::SetPosition(EVector position)
{
	m_box.SetPosition(position);
	SetHitboxPosition(position);
}
