#include "Player.h"
#include "Logger.h"

using KB = sf::Keyboard;

void Player::update(const float& dt)
{
	if (KB::isKeyPressed(KB::Right)) 
		move_units(vec2f(m_MovementSpeed, 0.f) * dt);
	else if (KB::isKeyPressed(KB::Left))
		move_units(vec2f(-m_MovementSpeed, 0.f) * dt);
	else if (KB::isKeyPressed(KB::Up))
		move_units(vec2f(0.f, -m_MovementSpeed) * dt);
	else if (KB::isKeyPressed(KB::Down))
		move_units(vec2f(0.f, m_MovementSpeed) * dt);
}

Player::Player()
{
	set_sprite("player", 48, 64 * 2, 48, 64);
	set_position(vec2f(.3f, .3f));
	set_scale(vec2f(1.5f, 1.5f));
	set_origin(vec2f(0.5f, 0.5f));
}

Player::~Player()
{
	LOG_WARN("Player object deleted");
}
