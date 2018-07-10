#include "EPhysics.h"
#include "EksisEngine.h"

EPhysics::EPhysics() : 
	p_flags(0),
	p_velocity(EVector(0,0)),
	p_mass(1.0f)
{
}

void EPhysics::SetFlag(int flags)
{
	p_flags = flags;
	GetPhysicsEngine()->SetPhysics(this);
}

void EPhysics::ToggleFlag(int flags)
{
	GetPhysicsEngine()->UnsetPhysics(this);
	p_flags = p_flags ^ flags;
}

char EPhysics::GetFlag()
{
	return p_flags;
}

void EPhysics::SetTag(int tags)
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

EVector EPhysics::GetVelocity()
{
	return p_velocity;
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

void EPhysics::SetHitboxPosition(EVector hitboxPosition)
{
	p_hitboxPosition = hitboxPosition;
}

void EPhysics::SetHitboxPosition(float width, float height)
{
	p_hitboxPosition = EVector(width, height);
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
