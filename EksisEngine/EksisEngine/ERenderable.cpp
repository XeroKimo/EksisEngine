#include "ERenderable.h"

ERenderable::ERenderable():
	m_position(EVector(0.0f, 0.0f)),
	m_origin(EVector(0.0f, 0.0f)),
	m_scale(EVector(1.0f, 1.0f))
{
}

ERenderable::ERenderable(float width, float height):
	m_width(width),
	m_height(height),
	m_position(EVector(0.0f, 0.0f)),
	m_origin(EVector(0.0f, 0.0f)),
	m_scale(EVector(1.0f, 1.0f))
{
}

ERenderable::~ERenderable()
{
}

void ERenderable::Initialize(float width, float height)
{
	m_width = width;
	m_height = height;
}

void ERenderable::SetPosition(float x, float y)
{
	m_position = EVector(x , y );
}

void ERenderable::SetPosition(EVector position)
{
	m_position = position;
}

void ERenderable::SetRotation(float radians)
{
	m_rotation = radians;
}

void ERenderable::SetOrigin(float x, float y)
{
	m_origin = EVector(x, y);
}

void ERenderable::SetOrigin(EVector origin)
{
	m_origin = origin;
}

void ERenderable::SetScale(float x, float y)
{
	m_scale = EVector(x, y);
}

void ERenderable::SetScale(EVector scale)
{
	m_scale = scale;
}

EMatrix ERenderable::GetMatrix()
{
	EMatrix anchor;
	anchor.SetPosition(EVector(-m_width * m_origin.x*m_scale.x, -m_height * m_origin.y*m_scale.y));
	EMatrix rotation;
	rotation.SetRotation(m_rotation);
	EMatrix position;
	position.SetPosition(EVector(m_position.x, m_position.y));
	EMatrix scale;
	scale.SetScale(EVector(m_scale.x, m_scale.y));
	return position *  rotation * anchor * scale;
}
