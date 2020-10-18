#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	Player(AssetsManager* assets_manager);
	virtual ~Player();
private:
	void update(float dt);

	float m_MovementSpeed = 300.f;
};

