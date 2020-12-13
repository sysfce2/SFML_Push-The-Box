#include "Player.h"
#include "Core/Logger.h"

using KB = sf::Keyboard;

void Player::update(const float& dt)
{
	m_Animation->update(dt);
	vec2f movement = { 0.f, 0.f };
	vec2f position = get_position_px();

	switch (m_AnimationState) {
	case AnState::Standing:
		if (m_PushedBox != nullptr) {
			m_PushedBox->m_CheckForTarget = true;
			m_PushedBox = nullptr;
		}
		if (m_StopWalking) {
			m_StopWalking = false;
			m_Animation->stop();
		}
		if (KB::isKeyPressed(KB::Right))     walk(Direction::Right);
		else if (KB::isKeyPressed(KB::Left)) walk(Direction::Left);
		else if (KB::isKeyPressed(KB::Up))   walk(Direction::Up);
		else if (KB::isKeyPressed(KB::Down)) walk(Direction::Down);
		break;
	case AnState::MovingUp:
		movement.y = -m_MovementSpeed * dt;
		if (position.y + movement.y < m_DestinationPos.y) {
			movement.y = m_DestinationPos.y - position.y;
			animate(AnState::Standing);
		}
		break;
	case AnState::MovingRight:
		movement.x = m_MovementSpeed * dt;
		if (position.x + movement.x > m_DestinationPos.x) {
			movement.x = m_DestinationPos.x - position.x;
			animate(AnState::Standing);
		}
		break;
	case AnState::MovingDown:
		movement.y = m_MovementSpeed * dt;
		if (position.y + movement.y > m_DestinationPos.y) {
			movement.y = m_DestinationPos.y - position.y;
			animate(AnState::Standing);
		}
		break;
	case AnState::MovingLeft:
		movement.x = -m_MovementSpeed * dt;
		if (position.x + movement.x < m_DestinationPos.x) {
			movement.x = m_DestinationPos.x - position.x;
			animate(AnState::Standing);
		}
		break;
	}

	if (movement.x != 0.f || movement.y != 0.f) {
		shift_px(movement);
		if (m_PushedBox != nullptr)
			m_PushedBox->shift_px(movement);
	}
}

void Player::walk(Direction direction)
{
	switch (direction) {
	case Direction::Up:
		if (can_walk({ 0, -1 })) {
			animate(AnState::MovingUp);
			m_DestinationPos.y -= m_TileMap->get_tile_size().y;
			m_TilePosition.y--;
		}
		break;
	case Direction::Right:
		if (can_walk({ 1, 0 })) {
			animate(AnState::MovingRight);
			m_DestinationPos.x += m_TileMap->get_tile_size().x;
			m_TilePosition.x++;
		}
		break;
	case Direction::Down:
		if (can_walk({ 0, 1 })) {
			animate(AnState::MovingDown);
			m_DestinationPos.y += m_TileMap->get_tile_size().y;
			m_TilePosition.y++;
		}
		break;
	case Direction::Left:
		if (can_walk({ -1, 0 })) {
			animate(AnState::MovingLeft);
			m_DestinationPos.x -= m_TileMap->get_tile_size().x;
			m_TilePosition.x--;
		}
		break;
	}
}

void Player::animate(AnState an_state)
{
	const uint8_t fps = 8;
	m_AnimationState = an_state;
	if (an_state != AnState::Standing)
		m_Animation->play_animation(m_AnName.at(an_state), fps, ANIMATE_REPEAT);
	else
		m_StopWalking = true;
}

bool Player::can_walk(vec2i offset)
{
	vec2i first = { (int)m_TilePosition.x + offset.x , (int)m_TilePosition.y + offset.y };
	if (first.x < 0 || first.y < 0)
		return false;

	if (m_TileMap->m_Map[first.x][first.y] == Tile::Wall)
		return false;

	vec2i second = { (int)m_TilePosition.x + offset.x * 2, (int)m_TilePosition.y + offset.y * 2 };
	if (second.x < 0 || second.y < 0)
		return false;

	if (m_TileMap->m_Map[first.x][first.y] == Tile::Box) {
		if (m_TileMap->m_Map[second.x][second.y] != Tile::None)
			return false;

		m_TileMap->m_Map[first.x][first.y] = Tile::None;
		m_TileMap->m_Map[second.x][second.y] = Tile::Box;

		for (Box* box : m_TileMap->m_Boxes)
			if (box->m_TilePos == vec2u(first.x, first.y)) {
				box->m_TilePos = { (unsigned)second.x, (unsigned)second.y };
				m_PushedBox = box;
				break;
			}
	}
	return true;
}

Player::Player(TileMap* tile_map) : m_TileMap(tile_map)
{
	set_sprite("player-sprite-sheet", { 0, 0 }, { 64, 64 });
	set_scale({ 1.5f, 1.5f });
	m_Animation = new Animation(this);
	m_Animation->set_sprite_sheet("player-sprite-sheet");
	m_Animation->new_animation("MovingDown", 0, 0, 64, 64, 9);
	m_Animation->new_animation("MovingUp", 0, 64, 64, 64, 9);
	m_Animation->new_animation("MovingRight", 0, 128, 64, 64, 9);
	m_Animation->new_animation("MovingLeft", 0, 192, 64, 64, 9);
	m_AnName[AnState::MovingUp] = "MovingUp";
	m_AnName[AnState::MovingRight] = "MovingRight";
	m_AnName[AnState::MovingDown] = "MovingDown";
	m_AnName[AnState::MovingLeft] = "MovingLeft";
}

Player::~Player()
{
	LOG_WARN("Player object deleted");
	delete m_Animation;
}
