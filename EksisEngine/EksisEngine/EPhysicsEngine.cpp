#include "EPhysicsEngine.h"

EPhysicsEngine::EPhysicsEngine()
{
}

void EPhysicsEngine::Shutdown()
{
	m_collidableVector.clear();
	m_moveableVector.clear();
	m_collidableVector.clear();
}

void EPhysicsEngine::SetPhysics(EPhysics * object)
{;
	char flags = object->GetFlag();
	if (flags & PhysicsFlags::GRAVITY)
	{
		m_gravityVector.push_back(object);
	}
	if (flags & PhysicsFlags::COLLIDABLE)
	{
		m_collidableVector.push_back(object);
	}
	if (flags & PhysicsFlags::MOVEABLE)
	{
		m_moveableVector.push_back(object);
	}
}

void EPhysicsEngine::UnsetPhysics(EPhysics * object)
{
	char flags = object->GetFlag();
	if (flags & PhysicsFlags::GRAVITY)
	{
		RemoveGravity(object);
	}
	if (flags & PhysicsFlags::COLLIDABLE)
	{
		RemoveCollidable(object);
	}
	if (flags & PhysicsFlags::MOVEABLE)
	{
		RemoveMoveable(object);
	}
}

void EPhysicsEngine::Update(double delta)
{
	ApplyGravity(delta);
	DetectCollision(delta);
}

void EPhysicsEngine::ApplyGravity(double delta)
{
	for (EPhysics* object : m_gravityVector)
	{
		object->SetAcceleration(0.0f, g_GRAVITY*delta*object->GetMass());
	}
}

void EPhysicsEngine::DetectCollision(double delta)
{
	if (m_collidableVector.size() >= 2)
	{
		for (std::vector<EPhysics*>::iterator i = m_collidableVector.begin(); i != m_collidableVector.end(); i++)
		{
			for (std::vector<EPhysics*>::iterator j = m_collidableVector.begin() + 1; j != m_collidableVector.end(); j++)
			{

			}
		}
	}
}

void EPhysicsEngine::MoveObjects(double delta)
{
}

void EPhysicsEngine::RemoveGravity(EPhysics * object)
{
}

void EPhysicsEngine::RemoveCollidable(EPhysics * object)
{
}

void EPhysicsEngine::RemoveMoveable(EPhysics * object)
{
}
