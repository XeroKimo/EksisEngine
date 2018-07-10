#include "EPhysicsEngine.h"

EPhysicsEngine::EPhysicsEngine()
{
}

void EPhysicsEngine::Shutdown()
{
	m_collidableVector.clear();
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
		object->ApplyForce(0.0f, g_GRAVITY*delta*delta*object->GetMass());
		//object->ApplyForce(g_GRAVITY*delta*delta*object->GetMass(),0.0f);

	}
}

void EPhysicsEngine::DetectCollision(double delta)
{
	if (m_collidableVector.size() >= 2)
	{
		for (std::vector<EPhysics*>::iterator i = m_collidableVector.begin(); i != m_collidableVector.end(); i++)
		{
			for (std::vector<EPhysics*>::iterator j = i + 1; j != m_collidableVector.end(); j++)
			{
				if (!IgnoreCollision((*i),(*j)))
				{
					int detection = EMath::SquareToSquareDetection(
					(*i)->GetHitboxPosition(),
					(*j)->GetHitboxPosition(),
					(*i)->GetHitbox(),
					(*j)->GetHitbox());
					if (detection)
					{
						MoveObjects(delta, (*i), (*j));
						if (detection == 2)
						{
							EVector oldVelocity = (*i)->GetVelocity();
							(*i)->SetVelocity(oldVelocity.x, oldVelocity.y*-1 * delta);
							oldVelocity = (*j)->GetVelocity();
							(*j)->SetVelocity(oldVelocity.x, oldVelocity.y*-1 * delta);
						}
						else
						{
							EVector oldVelocity = (*i)->GetVelocity();
							(*i)->SetVelocity(oldVelocity.x*-1 * delta, oldVelocity.y);
							oldVelocity = (*j)->GetVelocity();
							(*j)->SetVelocity(oldVelocity.x*-1 * delta, oldVelocity.y);
						}
					}
				}
			}
		}
	}
}

void EPhysicsEngine::MoveObjects(double delta, EPhysics* object1, EPhysics* object2)
{
	if (object1->GetFlag() & MOVEABLE)
	{

	}
	if (object2->GetFlag() & MOVEABLE)
	{

	}

}

bool EPhysicsEngine::IgnoreCollision(EPhysics * object1, EPhysics * object2)
{
	if (object1->GetIgnoreTag() & object2->GetTag() || object2->GetIgnoreTag() & object1->GetTag())
	{
		return true;
	}
	return false;
}

void EPhysicsEngine::RemoveGravity(EPhysics * object)
{
}

void EPhysicsEngine::RemoveCollidable(EPhysics * object)
{
}

