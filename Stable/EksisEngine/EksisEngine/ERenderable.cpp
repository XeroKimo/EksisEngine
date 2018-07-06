#include "ERenderable.h"

ERenderable::ERenderable():
	m_position(EVector(0.0f, 0.0f)),
	m_origin(EVector(0.0f, 0.0f)),
	m_scale(1.0f)
{
}

ERenderable::ERenderable(float width, float height):
	m_width(width*m_scale),
	m_height(height*m_scale),
	m_position(EVector(0.0f, 0.0f)),
	m_origin(EVector(0.0f, 0.0f)),
	m_scale(1.0f)
{
}

ERenderable::~ERenderable()
{
}

void ERenderable::SetDimensions(float width, float height)
{
	m_width = width * m_scale;
	m_height = height * m_scale;
}

void ERenderable::SetDimensions(EVector dimension)
{
	m_width = dimension.x*m_scale;
	m_height = dimension.y*m_scale;
}

void ERenderable::SetPosition(float x, float y)
{
	m_position = EVector(x , y );
}

void ERenderable::SetPosition(EVector position)
{
	m_position = position;
}

EVector ERenderable::GetPosition()
{
	return m_position;
}

void ERenderable::SetRotation(float radians)
{
	m_rotation = radians;
}

float ERenderable::GetRotation()
{
	return m_rotation;
}

void ERenderable::SetOrigin(float x, float y)
{
	m_origin = EVector(x, y);
}

void ERenderable::SetOrigin(EVector origin)
{
	m_origin = origin;
}

EVector ERenderable::GetOrigin()
{
	return m_origin;
}

void ERenderable::SetScale(float scale)
{
	m_scale = scale;
}

float ERenderable::GetScale()
{
	return m_scale;
}

EVector ERenderable::GetDimension()
{
	return EVector(m_width,m_height);
}


EMatrix ERenderable::GetMatrix()
{
	EMatrix anchor;
	anchor.SetPosition(EVector(-m_width * m_origin.x*m_scale, -m_height * m_origin.y*m_scale));
	EMatrix rotation;
	rotation.SetRotation(m_rotation);
	EMatrix position;
	position.SetPosition(EVector(m_position.x, m_position.y));
	EMatrix scale;
	scale.SetScale(m_scale);
	return position *  rotation * anchor * scale;
}
