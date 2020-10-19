#include "Wall.h"

void Wall::update(const float& dt)
{
}

Wall::Wall()
{
	set_sprite("wall");
	set_position(vec2f(200.f, 200.f));
	set_scale(vec2f(1.5f, 1.5f));
}

Wall::~Wall()
{
}
