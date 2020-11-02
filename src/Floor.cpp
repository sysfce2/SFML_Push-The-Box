#include "Floor.h"

void Floor::update(const float& dt)
{
}

Floor::Floor(const vec2f& place_pos)
{
	set_sprite("floor");
	set_position_px(place_pos);
	set_scale(vec2f(1.5f, 1.5f));
}

Floor::~Floor()
{
}
