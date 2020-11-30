#include "Wall.h"

void Wall::update(const float& dt)
{
}

Wall::Wall(const vec2f& position_px, uint8_t v)
{
	v %= 2;
	set_sprite("wall" + std::to_string(v));
	set_position_px(position_px);
	set_scale(vec2f(1.5f, 1.5f));
}

Wall::~Wall()
{
}
