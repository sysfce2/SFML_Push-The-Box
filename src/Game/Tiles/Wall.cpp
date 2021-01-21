#include "Wall.h"

Wall::Wall(vec2f place_pos, vec2u tile_pos, u8 v)
	: m_TilePos(tile_pos)
{
	v %= 2;
	set_position_px(place_pos);
	set_sprite("wall" + std::to_string(v));
}

void Wall::update(const float& dt)
{
}
