#include "Player.h"
#include "Logger.h"

using KB = sf::Keyboard;

void Player::update(const float& dt)
{
	switch (m_AnimationState) {
	case Standing:
	{
		if (KB::isKeyPressed(KB::Right)) move(Right);
		else if (KB::isKeyPressed(KB::Left)) move(Left);
		else if (KB::isKeyPressed(KB::Up)) move(Up);
		else if (KB::isKeyPressed(KB::Down)) move(Down);
		break;
	}
	case MovingUp:
	{
		move_units(vec2f(0.f, -m_MovementSpeed) * dt);
		if (m_PositionPx.y < m_DestinationPos.y) {
			m_PositionPx.y = m_DestinationPos.y;
			m_AnimationState = Standing;
		}
		break;
	}
	case MovingRight:
	{
		move_units(vec2f(m_MovementSpeed, 0.f) * dt);
		if (m_PositionPx.x > m_DestinationPos.x) {
			m_PositionPx.x = m_DestinationPos.x;
			m_AnimationState = Standing;
		}
		break;
	}
	case MovingDown:
	{
		move_units(vec2f(0.f, m_MovementSpeed) * dt);
		if (m_PositionPx.y > m_DestinationPos.y) {
			m_PositionPx.y = m_DestinationPos.y;
			m_AnimationState = Standing;
		}
		break;
	}
	case MovingLeft:
	{
		move_units(vec2f(-m_MovementSpeed, 0.f) * dt);
		if (m_PositionPx.x < m_DestinationPos.x) {
			m_PositionPx.x = m_DestinationPos.x;
			m_AnimationState = Standing;
		}
		break;
	}
	}
}

void Player::move(Direction direction)
{
	switch (direction) {
	case Up:
		if (can_move(m_TilePosition.x, m_TilePosition.y - 1)) {
			m_AnimationState = MovingUp;
			m_DestinationPos.y -= m_TileMap->get_tile_size().y;
			m_TilePosition.y--;
		}
		break;
	case Right:
		if (can_move(m_TilePosition.x + 1, m_TilePosition.y)) {
			m_AnimationState = MovingRight;
			m_DestinationPos.x += m_TileMap->get_tile_size().x;
			m_TilePosition.x++;
		}
		break;
	case Down:
		if (can_move(m_TilePosition.x, m_TilePosition.y + 1)) {
			m_AnimationState = MovingDown;
			m_DestinationPos.y += m_TileMap->get_tile_size().y;
			m_TilePosition.y++;
		}
		break;
	case Left:
		if (can_move(m_TilePosition.x - 1, m_TilePosition.y)) {
			m_AnimationState = MovingLeft;
			m_DestinationPos.x -= m_TileMap->get_tile_size().x;
			m_TilePosition.x--;
		}
		break;
	}

}

bool Player::can_move(uint16_t tile_x, uint16_t tile_y)
{
	return m_TileMap->get_map()[tile_x][tile_y] != t_Wall;
}

Player::Player(TileMap* tile_map)
	: m_TileMap(tile_map)
{
	set_sprite("player", 48, 64 * 2, 48, 64);
	set_scale(vec2f(1.5f, 1.5f));
}

Player::~Player()
{
	LOG_WARN("Player object deleted");
}
