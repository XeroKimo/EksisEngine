#pragma once
#include "EVector.h"
#include "EMatrix.h"

class ERenderable
{
public:
	ERenderable();
	ERenderable(float width, float height);
	~ERenderable();

	

	void SetPosition(float x, float y);
	void SetPosition(EVector position);
	EVector GetPosition();

	void SetRotation(float radians);
	float GetRotation();

	void SetOrigin(float x, float y);
	void SetOrigin(EVector origin);

	EVector GetOrigin();

	void SetScale(float scale);
	float GetScale();

	EVector GetDimension();


	virtual void Render() = 0;

	EMatrix GetMatrix();

private:
	float m_scale, m_width,m_height, m_rotation;
	EVector m_position, m_origin;
protected:
	void SetDimensions(float width, float height);
	void SetDimensions(EVector dimension);
};
