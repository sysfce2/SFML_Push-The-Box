#pragma once
#include "EntityState/Entity.h"

class Floor : public Entity
{
private:
	void update(const float& dt) override;
public:
	Floor(const vec2f& place_pos, uint8_t v, bool is_target = false);
	virtual ~Floor();
};