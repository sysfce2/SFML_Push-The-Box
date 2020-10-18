#pragma once
#include "Entity.h"

class Wall : public Entity
{
private:
	void update(float dt);
public:
	Wall(AssetsManager* assets_manager);
	virtual ~Wall();
};