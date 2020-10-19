#include "Player.h"
#include "Logger.h"

using KB = sf::Keyboard;

void Player::update(const float& dt)
{
	if (KB::isKeyPressed(KB::Right)) 
		m_Sprite.move(vec2f(m_MovementSpeed, 0.f) * dt);
	else if (KB::isKeyPressed(KB::Left))
		m_Sprite.move(vec2f(-m_MovementSpeed, 0.f) * dt);
	else if (KB::isKeyPressed(KB::Up))
		m_Sprite.move(vec2f(0.f, -m_MovementSpeed) * dt);
	else if (KB::isKeyPressed(KB::Down))
		m_Sprite.move(vec2f(0.f, m_MovementSpeed) * dt);
}

const vec2f Player::get_size_px()
{
	return vec2f(48 * get_scale().x, 64 * get_scale().y);
}

Player::Player()
{
	set_sprite("player", 48, 64 * 2, 48, 64);
	set_position(vec2f(.3f, .3f));
	set_scale(vec2f(1.5f, 1.5f));
	m_Sprite.setOrigin(vec2f(get_size_px().x / 2.f, get_size_px().y / 2.f));
}

Player::~Player()
{
	LOG_WARN("Player object deleted");
}
