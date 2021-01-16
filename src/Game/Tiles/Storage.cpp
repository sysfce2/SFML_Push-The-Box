#include "Storage.h"

Storage::Storage(vec2f place_pos, vec2u tile_pos)
	: m_TilePos(tile_pos)
{
	set_position_px(place_pos);
	set_sprite("storage");
	set_color({ 255,255,255,160 });
}

void Storage::update(const float& dt)
{
}
