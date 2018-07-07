#include "EPhysics.h"
#include "EksisEngine.h"

EPhysics::EPhysics() : 
	p_flags(0),
	p_velocity(EVector(0,0)),
	p_acceleration(EVector(0,0)),
	p_mass(1.0f)
{
}

void EPhysics::SetFlag(PhysicsFlags flags)
{
	p_flags = flags;
	GetPhysicsEngine()->SetPhysics(this);
}

void EPhysics::ToggleFlag(PhysicsFlags flags)
{
	GetPhysicsEngine()->UnsetPhysics(this);
	p_flags = p_flags ^ flags;
}

char EPhysics::GetFlag()
{
	return p_flags;
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
	return EVector();
}

void EPhysics::ApplyForce(EVector acceleration)
{
	p_acceleration += EVector(acceleration.x, acceleration.y);
}

void EPhysics::ApplyForce(float x, float y)
{
	p_acceleration += EVector(x, y);
}

void EPhysics::SetAcceleration(EVector acceleration)
{
	p_acceleration = acceleration;
}

void EPhysics::SetAcceleration(float x, float y)
{
	p_acceleration = EVector(x, y);
}

EVector EPhysics::GetAcceleration()
{
	return p_acceleration;
}

void EPhysics::SetMass(float mass)
{
	p_mass = mass;
}

float EPhysics::GetMass()
{
	return p_mass;
}
