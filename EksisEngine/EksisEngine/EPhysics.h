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

	void SetTag(ObjectTags tags);
	int GetTag();
	void SetIgnoreTag(int tags);
	int GetIgnoreTag();

	void SetVelocity(EVector velocity);
	void SetVelocity(float x, float y);
	void SetInstantVelocity(EVector velocity);
	void SetInstantVelocity(float x, float y);
	EVector GetVelocity();
	EVector GetInstantVelocity();
	EVector GetTotalVelocity();

	void ApplyForce(EVector acceleration);
	void ApplyForce(float x, float y);

	void SetHitbox(EVector hitbox);
	void SetHitbox(float width, float height);
	EVector GetHitbox();

	void SetHitboxOffset(EVector hitboxOffset);
	void SetHitboxOffest(float width, float height);
	EVector GetHitboxOffset();

	void SetHitboxPosition(EVector hitboxPosition);
	void SetHitboxPosition(float width, float height);
	EVector GetHitboxPosition();

	void SetMass(float mass);
	float GetMass();

	void SetInAir(bool air);
	bool GetInAir();
	void SetHitGround(bool collision);
	bool GetHitGround();

private:
	char p_flags;

	int p_objectTags;
	int p_ignoreTags;

	bool p_hitboxOffsetApplied;

	EVector p_hitbox;
	EVector p_hitboxOffset;
	EVector p_hitboxPosition;


	bool p_hitGround;

protected:
	bool p_inAir;

	EVector p_velocity;
	EVector p_instantVelocity;
	EVector p_totalVelocity;
	float p_mass;

	
};