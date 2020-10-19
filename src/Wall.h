#pragma once
#include "Entity.h"

class Wall : public Entity
{
private:
	void update(const float& dt);
public:
	Wall();
	virtual ~Wall();
};