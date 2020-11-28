#pragma once
#include "EntityState/Entity.h"

class Box : public Entity
{
private:
	void update(const float& dt) override;
	std::vector<vec2u>* m_TargetsPtr = nullptr;
	uint16_t* m_BoxesOnTargetsPtr = nullptr;
public:
	vec2u m_TilePos;
	bool m_CheckForTarget = true;
	bool m_IsOnTarget = false;
	Box(const vec2f& place_pos, vec2u tile_pos, std::vector<vec2u>* tp, uint16_t* btp);
	virtual ~Box();
};