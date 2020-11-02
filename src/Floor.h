#pragma once
#include "Entity.h"

class Floor : public Entity
{
private:
	void update(const float& dt);
public:
	Floor(const vec2f& place_pos);
	virtual ~Floor();
};