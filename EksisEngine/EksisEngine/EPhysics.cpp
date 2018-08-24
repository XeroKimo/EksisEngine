#include "EPhysics.h"
#include "EksisEngine.h"

EPhysics::EPhysics() :
	p_flags(0),
	p_velocity(EVector(0, 0)),
	p_mass(1.0f),
	p_inAir(true),
	p_hitboxOffsetApplied(false)
{
}

void EPhysics::SetFlag(int flags)
{
	GetPhysicsEngine()->UnsetPhysics(this);
	p_flags = flags;
	GetPhysicsEngine()->SetPhysics(this);
}

void EPhysics::ToggleFlag(int flags)
{
	GetPhysicsEngine()->UnsetPhysics(this);
	p_flags = p_flags ^ flags;
	GetPhysicsEngine()->SetPhysics(this);
}

char EPhysics::GetFlag()
{
	return p_flags;
}

void EPhysics::SetTag(ObjectTags tags)
{
	p_objectTags = tags;
}

int EPhysics::GetTag()
{
	return p_objectTags;
}

void EPhysics::SetIgnoreTag(int tags)
{
	p_ignoreTags = tags;
}

int EPhysics::GetIgnoreTag()
{
	return p_ignoreTags;
}

void EPhysics::SetVelocity(EVector velocity)
{
	p_velocity = velocity;
}

void EPhysics::SetVelocity(float x, float y)
{
	p_velocity = EVector(x, y);
}

void EPhysics::SetInstantVelocity(EVector velocity)
{
	p_instantVelocity = velocity;
}

void EPhysics::SetInstantVelocity(float x, float y)
{
	p_instantVelocity = EVector(x, y);
}

EVector EPhysics::GetVelocity()
{
	return p_velocity;
}

EVector EPhysics::GetInstantVelocity()
{
	return p_instantVelocity;
}

EVector EPhysics::GetTotalVelocity()
{
	return p_totalVelocity;
}

void EPhysics::ApplyForce(EVector acceleration)
{
	p_velocity += EVector(acceleration);
}

void EPhysics::ApplyForce(float x, float y)
{
	p_velocity += EVector(x, y);
}			  
			  
void EPhysics::SetHitbox(EVector hitbox)
{
	p_hitbox = hitbox;
}

void EPhysics::SetHitbox(float width, float height)
{
	p_hitbox = EVector(width, height);
}

EVector EPhysics::GetHitbox()
{
	return p_hitbox;
}

void EPhysics::SetHitboxOffset(EVector hitboxOffset)
{
	p_hitboxOffset = hitboxOffset;
	p_hitboxOffsetApplied = false;
}

void EPhysics::SetHitboxOffest(float width, float height)
{
	p_hitboxOffset = EVector(width, height);
	p_hitboxOffsetApplied = false;
}

EVector EPhysics::GetHitboxOffset()
{
	return p_hitboxOffset;
}

void EPhysics::SetHitboxPosition(EVector hitboxPosition)
{
	if (p_hitboxOffsetApplied == false)
	{
		p_hitboxPosition = hitboxPosition + p_hitboxOffset;
		p_hitboxOffsetApplied = true;
	}
	else
	{
		p_hitboxPosition = hitboxPosition;
	}
}

void EPhysics::SetHitboxPosition(float width, float height)
{
	if (p_hitboxOffsetApplied == false)
	{
		p_hitboxPosition = EVector(width, height) + p_hitboxOffset;
		p_hitboxOffsetApplied = true;
	}
	else
	{
		p_hitboxPosition = EVector(width, height);
	}
}

EVector EPhysics::GetHitboxPosition()
{
	return p_hitboxPosition;
}


void EPhysics::SetMass(float mass)
{
	p_mass = mass;
}

float EPhysics::GetMass()
{
	return p_mass;
}

void EPhysics::SetInAir(bool air)
{
	p_inAir = air;
}

bool EPhysics::GetInAir()
{
	return p_inAir;
}

void EPhysics::SetHitGround(bool collision)
{
	p_hitGround = collision;
}

bool EPhysics::GetHitGround()
{
	return p_hitGround;
}
