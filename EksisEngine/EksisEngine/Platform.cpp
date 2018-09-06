#include "Platform.h"

Platform::Platform()
{
	SetFlag(COLLIDABLE);
	SetTag(TAG_PLATFORM);
	SetIgnoreTag(TAG_PLATFORM);

	m_platform.SetColor(1.0f, 0.0f, 0.0f);
	SetHitbox(m_platform.GetDimension());
	SetHitboxPosition(m_platform.GetPosition() - (m_platform.GetDimension() * m_platform.GetOrigin()));
}

Platform::~Platform()
{

}

void Platform::Update(double delta)
{
	SetHitboxPosition(m_platform.GetPosition() - (m_platform.GetDimension() * m_platform.GetOrigin()));
}

void Platform::Render()
{
	m_platform.Render();
}

void Platform::Input(EInput* input)
{
}

ESquare & Platform::GetSquare()
{
	return m_platform;
}
