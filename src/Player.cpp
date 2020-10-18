#include "Player.h"
#include "Logger.h"

using KB = sf::Keyboard;

void Player::update(float dt)
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

Player::Player(AssetsManager* assets_manager)
	: Entity(assets_manager)
{
	set_sprite("player", 48, 64 * 2, 48, 64);
	set_position(vec2f(100.f, 100.f));
	set_scale(vec2f(1.5f, 1.5f));
}

Player::~Player()
{
	LOG_WARN("Player object deleted");
}
