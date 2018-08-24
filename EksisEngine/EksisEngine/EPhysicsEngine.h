#pragma once
#include "EPhysics.h"
#include <vector>

const float g_GRAVITY = -3000.0f;

class EPhysicsEngine
{
public:
	EPhysicsEngine();

	void Shutdown();

	void SetPhysics(EPhysics* object);
	void UnsetPhysics(EPhysics* object);

	void Update(double delta);
private:
	std::vector<EPhysics*> m_gravityVector;
	std::vector<EPhysics*> m_collidableVector;
private:
	void ApplyGravity(double delta);
	void DetectCollision(double delta);
	void MoveObjects(double delta, EPhysics* object1, EPhysics* object2);

	bool CheckCollision(EPhysics* object1, EPhysics* object2);
	bool IgnoreCollision(EPhysics* object1, EPhysics* object2);

	float CorrectHitBox(EPhysics* object1, EPhysics* object2, int axis);
	void MoveHitBoxes(EPhysics* object1, EPhysics* object2, float distance, bool yAxis, int side);
	
	void RemoveGravity(EPhysics* object);
	void RemoveCollidable(EPhysics* object);
};

