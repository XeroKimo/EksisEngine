#pragma once
#include "ERenderable.h"

class Camera :public ERenderable
{
public:
	Camera();
	void AttachCameraToObject(ERenderable* object);
	void DetachCameraFromObject();
	void SetCameraOffset(EVector offset);
	void SetCameraOFfset(float x, float y);
	void SetID(int ID);

	void Render();
	void Update(double delta);
private:
	EVector m_cameraOffset;
	ERenderable* m_object;
	int playerID;
	EVector quadrant;
};