#pragma once
#include "Entity/Entity.h"

class Floor : public Entity
{
public:
	Floor(vec2f place_pos, vec2u tile_size, u8 v);
	virtual ~Floor() = default;
private:
	void update(const float& dt) override;
	vec2u m_TilePos;
};