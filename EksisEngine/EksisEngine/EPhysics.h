#pragma once
#include "EMathLib.h"

enum PhysicsFlags {
	GRAVITY = 0b00000001,
	COLLIDABLE = 0b00000010,
	MOVEABLE = 0b00000100
};

enum ObjectTags {
	TAG_PLAYER = 1,
	TAG_PLATFORM = 2
};

class EPhysics
{
public:
	EPhysics();

	void SetFlag(int flags);
	void ToggleFlag(int flags);
	char GetFlag();

	void SetTag(int tags);
	int GetTag();

	void SetIgnoreTag(int tags);
	int GetIgnoreTag();

	void SetVelocity(EVector velocity);
	void SetVelocity(float x, float y);
	EVector GetVelocity();

	void ApplyForce(EVector acceleration);
	void ApplyForce(float x, float y);

	void SetHitbox(EVector hitbox);
	void SetHitbox(float width, float height);
	EVector GetHitbox();

	void SetHitboxPosition(EVector hitboxPosition);
	void SetHitboxPosition(float width, float height);
	EVector GetHitboxPosition();

	void SetMass(float mass);
	float GetMass();

private:
	char p_flags;
	int p_objectTags;
	int p_ignoreTags;
	EVector p_hitbox;
	EVector p_hitboxPosition;

protected:
	EVector p_velocity;
	float p_mass;

	
};