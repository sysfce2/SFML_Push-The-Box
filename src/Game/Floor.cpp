#include "Floor.h"

void Floor::update(const float& dt)
{
}

Floor::Floor(const vec2f& place_pos, uint8_t v, bool is_target)
{
	v %= 4;
	if (is_target)
		set_sprite("target");
	else
		set_sprite("floor" + std::to_string(v + 1));
	set_position_px(place_pos);
	set_scale({ 1.5f, 1.5f });
}
