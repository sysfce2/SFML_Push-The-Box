#pragma once
#include "Entity/Entity.h"

class Storage : public Entity 
{
public:
	Storage(vec2f place_pos, vec2u tile_pos);
	virtual ~Storage() = default;
private:
	void update(const float& dt) override;
	vec2u m_TilePos;
};