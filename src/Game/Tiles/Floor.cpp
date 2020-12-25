#include "Floor.h"

Floor::Floor(vec2f place_pos, vec2u tile_size, uint8_t v)
	: m_TilePos(tile_size)
{
	v %= 4;
	set_position_px(place_pos);
	set_sprite("floor0");

}

void Floor::update(const float& dt)
{
}