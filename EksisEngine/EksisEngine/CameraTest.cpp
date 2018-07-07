#include "CameraTest.h"
#include "EksisEngine.h"

Camera::Camera() :
	m_object(nullptr)
{
}

void Camera::AttachCameraToObject(ERenderable * object)
{
	m_object = object;
}

void Camera::DetachCameraFromObject()
{
	m_object = nullptr;
}

void Camera::SetCameraOffset(EVector offset)
{
	m_cameraOffset = offset;
}

void Camera::SetCameraOFfset(float x, float y)
{
	m_cameraOffset = EVector(x, y);
}

void Camera::SetID(int ID)
{
	playerID = ID;
	if (ID == 1)
	{
		SetScale(0.5f);
		quadrant = EVector(0.0f, 360.0f);
		SetPosition(0.0f, 360.0f);
	}
	if (ID == 2)
	{
		SetScale(0.5f);
		quadrant = EVector(640.0f, 0.0f);
		SetPosition(640.0f, 0.0f);
	}
}

void Camera::Render()
{
	if (playerID != 0)
	EksisEngine::GetInstance()->GetShader()->SetSubView(GetMatrix());
	else
	{
		EksisEngine::GetInstance()->GetShader()->SetSubView(EMatrix::Identity());
	}
}

void Camera::Update(double delta)
{
	if (m_object != nullptr)
	{
		SetPosition(m_object->GetPosition().x *-1 * GetScale() + m_cameraOffset.x + quadrant.x, m_object->GetPosition().y * -1 * GetScale() + m_cameraOffset.y + quadrant.y);
	}
}
