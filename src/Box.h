#pragma once
#include "Entity.h"

class Box : public Entity
{
private:
	void update(const float& dt);
public:
	Box(const vec2f& place_pos);
	virtual ~Box();
};