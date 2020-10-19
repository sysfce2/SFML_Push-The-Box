#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	const vec2f get_size_px();
	Player();
	virtual ~Player();
private:
	void update(const float& dt);

	float m_MovementSpeed = 300.f;
};

