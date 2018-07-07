#pragma once
#include "EVector.h"
#include "EMatrix.h"

class ERenderable
{
public:
	ERenderable();
	ERenderable(float width, float height);
	~ERenderable();

	void Initialize(float width, float height);

	void SetPosition(float x, float y);
	void SetPosition(EVector position);

	void SetRotation(float radians);

	void SetOrigin(float x, float y);
	void SetOrigin(EVector origin);

	void SetScale(float x, float y);
	void SetScale(EVector scale);


	virtual void Render() = 0;

	EMatrix GetMatrix();

private:
	float m_width,m_height, m_rotation;
	EVector m_position, m_origin, m_scale;
};
