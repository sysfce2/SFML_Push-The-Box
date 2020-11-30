#pragma once
#include "Entity/Entity.h"

class Box : public Entity
{
private:
	void update(const float& dt) override;
public:
	vec2u m_TilePos;
	bool m_CheckForTarget = true;
	bool m_IsOnTarget = false;
	Box(const vec2f& place_pos, vec2u tile_pos);
	virtual ~Box() = default;
};