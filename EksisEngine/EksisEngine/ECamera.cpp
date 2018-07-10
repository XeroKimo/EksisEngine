#include "ECamera.h"
#include "EksisEngine.h"

ECamera::ECamera() :
	m_object(nullptr),
	m_cameraOffset(GetClientWidth() / 2, GetClientHeight() / 2)
{
}

void ECamera::AttachCameraToObject(ERenderable * object)
{
	m_object = object;
}

void ECamera::AttachElementToCamera(ERenderable * object)
{
	m_cameraHUD.push_back(object);
	m_cameraHUDOffset[object] = object->GetPosition();
}

void ECamera::SetCameraOffset(EVector offset)
{
	m_cameraOffset = offset;
}

void ECamera::SetCameraOFfset(float x, float y)
{
	m_cameraOffset = EVector(x, y);
}

void ECamera::Render()
{
	for (int i =0; i!= m_cameraHUD.size();i++)
	{
		m_cameraHUD[i]->Render();
	}
}

void ECamera::Update(double delta)
{
	if (m_object != nullptr)
	{
		SetPosition(m_object->GetPosition().x *-1 + m_cameraOffset.x, m_object->GetPosition().y * -1 + m_cameraOffset.y);
	}
	for (int i = 0; i != m_cameraHUD.size(); i++)
	{
		EVector position = m_cameraHUDOffset[m_cameraHUD[i]];
		m_cameraHUD[i]->SetPosition(position.x-GetPosition().x  ,position.y-GetPosition().y);



	}
}
