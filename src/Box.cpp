#include "Box.h"

void Box::update(const float& dt)
{
}

Box::Box(const vec2f& place_pos)
{
	set_sprite("box");
	set_position_px(place_pos);
	set_scale(vec2f(0.1875f, 0.1875f));
}

Box::~Box()
{
}
