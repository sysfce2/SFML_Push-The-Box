#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	Player();
	virtual ~Player();
private:
	void update(const float& dt);

	float m_MovementSpeed = 250.f;
};

