#pragma once
#include "Entity.h"

class Player : public Entity
{
private:
	void update(float dt);
public:
	Player(AssetsManager* assets_manager);
	virtual ~Player();
};

