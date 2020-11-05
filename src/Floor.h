#pragma once
#include "Entity.h"

class Floor : public Entity
{
private:
	void update(const float& dt) override;
public:
	Floor(const vec2f& place_pos, bool is_target = false);
	virtual ~Floor();
};