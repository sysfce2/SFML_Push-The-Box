#include "Floor.h"

void Floor::update(const float& dt)
{
}

Floor::Floor(const vec2f& place_pos, bool is_target)
{
	if (is_target)
		set_sprite("target");
	else
		set_sprite("floor");
	set_position_px(place_pos);
	set_scale(vec2f(1.5f, 1.5f));
}

Floor::~Floor()
{
}
