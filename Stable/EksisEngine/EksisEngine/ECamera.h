#pragma once
#include "ERenderable.h"
#include "EVector.h"
#include <vector>
#include <map>

class ECamera : public ERenderable
{
public:
	ECamera();

	void AttachCameraToObject(ERenderable* object);
	void AttachElementToCamera(ERenderable* object);
	void SetCameraOffset(EVector offset);
	void SetCameraOFfset(float x, float y);

	void Render();
	void Update(double delta);
private:
	std::vector<ERenderable*> m_cameraHUD;
	std::map<ERenderable*, EVector> m_cameraHUDOffset;
	EVector m_cameraOffset;
	ERenderable* m_object;
};