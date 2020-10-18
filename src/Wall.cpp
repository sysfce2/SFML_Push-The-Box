#include "Wall.h"

void Wall::update(float dt)
{
}

Wall::Wall(AssetsManager* assets_manager)
	: Entity(assets_manager)
{
	set_sprite("wall");
	set_position(vec2f(200.f, 200.f));
	set_scale(vec2f(1.5f, 1.5f));
}

Wall::~Wall()
{
}
