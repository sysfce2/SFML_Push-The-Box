#include "Player.h"

void Player::update(float dt)
{
}

Player::Player(AssetsManager* assets_manager)
	: Entity(assets_manager)
{
	set_sprite("player", 48, 64 * 2, 48, 64);
	set_position(vec2f(100.f, 100.f));
	set_scale(vec2f(2.f, 2.f));
}

Player::~Player()
{
}
