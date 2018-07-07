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

void ECamera::DetachCameraFromObject()
{
	m_object = nullptr;
}

void ECamera::AttachElementToCamera(ERenderable * object)
{
	m_cameraHUD.push_back(object);
	m_cameraHUDOffset[object] = object->GetPosition();
}

void ECamera::DetachElementFromCamera(ERenderable* object)
{
	m_cameraHUDOffset.erase(object);
	for (int i = 0; i < m_cameraHUD.size(); i++)
	{
		if (m_cameraHUD[i] == object && m_cameraHUD[i] == m_cameraHUD.back())
		{
			m_cameraHUD.pop_back();
		}
		else
		{
			m_cameraHUD.push_back(object);
			if (m_cameraHUD.size() <= 3)
				m_cameraHUD[i] = m_cameraHUD.at(m_cameraHUD.size() - 1);
			else
				m_cameraHUD[i] = m_cameraHUD.at(m_cameraHUD.size() - 2);
			m_cameraHUD.pop_back();
			m_cameraHUD.pop_back();
		}
	}
}

void ECamera::ClearElementsFromCamera()
{
	m_cameraHUD.clear(); 
	m_cameraHUDOffset.clear();
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
