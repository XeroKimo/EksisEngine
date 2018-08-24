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
		if (object->GetInAir() == true)
		object->ApplyForce(0.0f, g_GRAVITY*delta*delta*object->GetMass());
	}
}

void EPhysicsEngine::DetectCollision(double delta)
{
	if (m_collidableVector.size() >= 2)
	{
		for (EPhysics* object : m_collidableVector)
		{
			object->SetHitGround(false);
		}
		for (std::vector<EPhysics*>::iterator i = m_collidableVector.begin(); i != m_collidableVector.end(); i++)
		{
			for (std::vector<EPhysics*>::iterator j = i + 1; j != m_collidableVector.end(); j++)
			{
				if (!IgnoreCollision((*i),(*j)))
				{
					if(CheckCollision((*i), (*j)))
						MoveObjects(delta, (*i), (*j));
				}
			}
			if ((*i)->GetHitGround() == false)
			{
				(*i)->SetInAir(true);
			}
		}
	}
}

void EPhysicsEngine::MoveObjects(double delta, EPhysics* object1, EPhysics* object2)
{
	if ((object1->GetFlag() & MOVEABLE)&& (object2->GetFlag() & MOVEABLE))
	{
		object1->SetInstantVelocity(object2->GetTotalVelocity() - object1->GetInstantVelocity());
		object2->SetInstantVelocity(object1->GetTotalVelocity() - object2->GetInstantVelocity());

	}

}

bool EPhysicsEngine::CheckCollision(EPhysics * object1, EPhysics * object2)
{
	int detection = EMath::SquareToSquareDetection(
		object1->GetHitboxPosition(),
		object2->GetHitboxPosition(),
		object1->GetHitbox(),
		object2->GetHitbox());
	if (detection)
	{
		float correctHitBox = CorrectHitBox(object1, object2, detection);
		if (detection > 2)
		{
			if (detection == 3)
			{
				if ((object2->GetFlag() & GRAVITY) && object2->GetHitGround() == false)
				{
					object2->SetHitGround(true);
					object2->SetInAir(false);
				}
				MoveHitBoxes(object1, object2, correctHitBox, true, 1);
			}
			if (detection == 4)
			{
				if ((object1->GetFlag() & GRAVITY) && object1->GetHitGround() == false)
				{
					object1->SetHitGround(true);
					(object1)->SetInAir(false);
				}
				MoveHitBoxes(object1, object2, correctHitBox, true, -1);
			}
			if ((object2->GetFlag() & MOVEABLE) == false || object1->GetHitGround() == true)
			{
				object1->SetVelocity(object1->GetVelocity().x, 0.0f);
				object1->SetInstantVelocity(object1->GetInstantVelocity().x, 0.0f);
			}
			if ((object1->GetFlag() & MOVEABLE) == false || object2->GetHitGround() == true)
			{
				object2->SetVelocity(object2->GetVelocity().x, 0.0f);
				object2->SetInstantVelocity(object2->GetInstantVelocity().x, 0.0f);
			}
		}
		else
		{
			if ((object2->GetFlag() & MOVEABLE))
			{
				object1->SetVelocity(0.0f, object1->GetVelocity().y);
			}
			if ((object1->GetFlag() & MOVEABLE))
			{
				object2->SetVelocity(0.0f, object2->GetVelocity().y);
			}
			if (detection == 1)
			{
				MoveHitBoxes(object1, object2, correctHitBox, false, 1);

			}
			if (detection == 2)
			{	
				MoveHitBoxes(object1, object2, correctHitBox, false, -1);
			}
		}

		return true;
	}
	return false;
}

bool EPhysicsEngine::IgnoreCollision(EPhysics * object1, EPhysics * object2)
{
	if (object1->GetIgnoreTag() & object2->GetTag() || object2->GetIgnoreTag() & object1->GetTag())
	{
		return true;
	}
	return false;
}

float EPhysicsEngine::CorrectHitBox(EPhysics * object1, EPhysics * object2, int axis)
{
	if (axis == 1)
	{
		return EMath::xAxisCheck(object1->GetHitboxPosition(), object2->GetHitboxPosition(), object1->GetHitbox(), object2->GetHitbox());
	}
	else if (axis == 2)
	{
		return EMath::xAxisCheck(object2->GetHitboxPosition(), object1->GetHitboxPosition(), object2->GetHitbox(), object1->GetHitbox());
	}	
	else if (axis == 3)
	{
		return EMath::yAxisCheck(object1->GetHitboxPosition(), object2->GetHitboxPosition(), object1->GetHitbox(), object2->GetHitbox());
	}
	else if (axis == 4)
	{
		return EMath::yAxisCheck(object2->GetHitboxPosition(), object1->GetHitboxPosition(), object2->GetHitbox(), object1->GetHitbox());
	}
}

void EPhysicsEngine::MoveHitBoxes(EPhysics * object1, EPhysics * object2, float distance, bool yAxis, int side)
{
	if (yAxis)
	{
		if ((object1->GetFlag() & MOVEABLE) && (object2->GetFlag() & MOVEABLE))
		{
			float half = distance / 2;
			object1->SetHitboxPosition(object1->GetHitboxPosition().x, object1->GetHitboxPosition().y + half * -side);
			object2->SetHitboxPosition(object2->GetHitboxPosition().x, object2->GetHitboxPosition().y + half * side);
		}
		else if ((object1->GetFlag() & MOVEABLE))
		{
			object1->SetHitboxPosition(object1->GetHitboxPosition().x, object1->GetHitboxPosition().y + distance * -side);
		}
		else
		{
			object2->SetHitboxPosition(object2->GetHitboxPosition().x, object2->GetHitboxPosition().y + distance * side);
		}
	}
	else
	{
		if ((object1->GetFlag() & MOVEABLE) && (object2->GetFlag() & MOVEABLE))
		{
			float half = distance / 2;
			object1->SetHitboxPosition(object1->GetHitboxPosition().x + half * -side, object1->GetHitboxPosition().y);
			object2->SetHitboxPosition(object2->GetHitboxPosition().x + half * side, object2->GetHitboxPosition().y);
		}
		else if ((object1->GetFlag() & MOVEABLE))
		{
			object1->SetHitboxPosition(object1->GetHitboxPosition().x + distance * -side, object1->GetHitboxPosition().y);
		}
		else
		{
			object2->SetHitboxPosition(object2->GetHitboxPosition().x + distance * side, object2->GetHitboxPosition().y);
		}
	}
}

void EPhysicsEngine::RemoveGravity(EPhysics * object)
{
	for (int i = 0; i <m_gravityVector.size(); i++)
	{
		if (m_gravityVector[i] == object && m_gravityVector[i] == m_gravityVector.back())
		{
			m_gravityVector.pop_back();
		}
		else if (m_gravityVector[i] == object)
		{
			m_gravityVector.push_back(object);
			if (m_gravityVector.size() <= 3)
				m_gravityVector[i] = m_gravityVector.at(m_gravityVector.size() - 1);
			else
				m_gravityVector[i] = m_gravityVector.at(m_gravityVector.size() - 2);
			m_gravityVector.pop_back();
			m_gravityVector.pop_back();
		}
	}
}

void EPhysicsEngine::RemoveCollidable(EPhysics * object)
{
	for (int i = 0; i < m_collidableVector.size(); i++)
	{
		if (m_collidableVector[i] == object && m_collidableVector[i] == m_collidableVector.back())
		{
			m_collidableVector.pop_back();
		}
		else if (m_collidableVector[i] == object)
		{
			m_collidableVector.push_back(object);
			if (m_collidableVector.size() <= 3)
				m_collidableVector[i] = m_collidableVector.at(m_collidableVector.size() - 1);
			else
				m_collidableVector[i] = m_collidableVector.at(m_collidableVector.size() - 2);
			m_collidableVector.pop_back();
			m_collidableVector.pop_back();
		}
	}
}

