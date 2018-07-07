#pragma once
#include "EMath.h"

enum PhysicsFlags {
	GRAVITY = 0b00000001,
	COLLIDABLE = 0b00000010,
	MOVEABLE = 0b00000100
};

class EPhysics
{
public:
	EPhysics();

	void SetFlag(PhysicsFlags flags);
	void ToggleFlag(PhysicsFlags flags);
	char GetFlag();


	void SetVelocity(EVector velocity);
	void SetVelocity(float x, float y);
	EVector GetVelocity();

	void ApplyForce(EVector acceleration);
	void ApplyForce(float x, float y);

	void SetAcceleration(EVector acceleration);
	void SetAcceleration(float x, float y);
	EVector GetAcceleration();

	void SetMass(float mass);
	float GetMass();

private:
	char p_flags;

protected:
	EVector p_velocity;
	EVector p_acceleration;
	float p_mass;
	
};