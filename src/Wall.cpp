#include "Wall.h"

void Wall::update(const float& dt)
{
}

Wall::Wall(const vec2f& position_px)
{
	set_sprite("wall");
	set_position_px(position_px);
	set_scale(vec2f(1.5f, 1.5f));
}

Wall::~Wall()
{
}
