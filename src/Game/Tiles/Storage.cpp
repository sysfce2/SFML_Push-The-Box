#include "Storage.h"

Storage::Storage(vec2f place_pos, vec2u tile_pos)
	: m_TilePos(tile_pos)
{
	set_position_px(place_pos);
	set_sprite("storage");
}

void Storage::update(const float& dt)
{
}
