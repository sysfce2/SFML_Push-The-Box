#include "Player.h"
#include "Core/Logger.h"

using KB = sf::Keyboard;

void Player::update(const float& dt)
{
	m_Animation->update(dt);
	vec2f movement = { 0.f, 0.f };
	vec2f position = get_position_px();

	if (m_AnimationState == Standing){
		if (m_PushedBox != nullptr) {
			m_PushedBox->m_CheckForTarget = true;
			m_PushedBox = nullptr;
		}

		if (m_StandingWait < 1)
			if (++m_StandingWait == 1)
				m_Animation->start_stop();

			
		if (KB::isKeyPressed(KB::Right))     move(Right);
		else if (KB::isKeyPressed(KB::Left)) move(Left);
		else if (KB::isKeyPressed(KB::Up))   move(Up);
		else if (KB::isKeyPressed(KB::Down)) move(Down);
	}
	else if (m_AnimationState == MovingUp) {
		movement.y = -m_MovementSpeed * dt;
		if (position.y + movement.y < m_DestinationPos.y) {
			movement.y = m_DestinationPos.y - position.y;
			animate(Standing);
		}
	}
	else if (m_AnimationState == MovingRight) {
		movement.x = m_MovementSpeed * dt;
		if (position.x + movement.x > m_DestinationPos.x) {
			movement.x = m_DestinationPos.x - position.x;
			animate(Standing);
		}
	}
	else if (m_AnimationState == MovingDown) {
		movement.y = m_MovementSpeed * dt;
		if (position.y + movement.y > m_DestinationPos.y) {
			movement.y = m_DestinationPos.y - position.y;
			animate(Standing);
		}
	}
	else if (m_AnimationState == MovingLeft) {
		movement.x = -m_MovementSpeed * dt;
		if (position.x + movement.x < m_DestinationPos.x) {
			movement.x = m_DestinationPos.x - position.x;
			animate(Standing);
		}
	}

	if (movement.x != 0.f || movement.y != 0.f) {
		move_px(movement);
		if (m_PushedBox != nullptr)
			m_PushedBox->move_px(movement);
	}
}

void Player::move(Direction direction)
{
	switch (direction) {
	case Up:
		if (can_move({ 0, -1 })) {
			animate(MovingUp);
			m_DestinationPos.y -= m_TileMap->get_tile_size().y;
			m_TilePosition.y--;
		}
		break;
	case Right:
		if (can_move({ 1, 0 })) {
			animate(MovingRight);
			m_DestinationPos.x += m_TileMap->get_tile_size().x;
			m_TilePosition.x++;
		}
		break;
	case Down:
		if (can_move({ 0, 1 })) {
			animate(MovingDown);
			m_DestinationPos.y += m_TileMap->get_tile_size().y;
			m_TilePosition.y++;
		}
		break;
	case Left:
		if (can_move({ -1, 0 })) {
			animate(MovingLeft);
			m_DestinationPos.x -= m_TileMap->get_tile_size().x;
			m_TilePosition.x--;
		}
		break;
	}

}

void Player::animate(AnimationState an_state)
{
	const uint8_t fps = 8;
	switch (an_state) {
	case Standing:
		m_AnimationState = Standing;
		m_StandingWait = 0;
		break;
	case MovingUp:
		m_AnimationState = MovingUp;
		m_Animation->play_animation("MovingUp", fps, AN_REPEAT);
		break;
	case MovingRight:
		m_AnimationState = MovingRight;
		m_Animation->play_animation("MovingRight", fps, AN_REPEAT);
		break;
	case MovingDown:
		m_AnimationState = MovingDown;
		m_Animation->play_animation("MovingDown", fps, AN_REPEAT);
		break;
	case MovingLeft:
		m_AnimationState = MovingLeft;
		m_Animation->play_animation("MovingLeft", fps, AN_REPEAT);
		break;
	default:
		break;
	}
}

bool Player::can_move(vec2i offset)
{
	vec2i first = { (int)m_TilePosition.x + offset.x , (int)m_TilePosition.y + offset.y };
	if (first.x < 0 || first.y < 0)
		return false;

	if (m_TileMap->m_Map[first.x][first.y] == t_Wall)
		return false;

	vec2i second = { (int)m_TilePosition.x + offset.x * 2, (int)m_TilePosition.y + offset.y * 2 };
	if (second.x < 0 || second.y < 0)
		return false;

	if (m_TileMap->m_Map[first.x][first.y] == t_Box) {
		if (m_TileMap->m_Map[second.x][second.y] != t_None)
			return false;

		m_TileMap->m_Map[first.x][first.y] = t_None;
		m_TileMap->m_Map[second.x][second.y] = t_Box;

		for (Box* box : m_TileMap->m_Boxes) {
			if (box->m_TilePos == vec2u(first.x, first.y)) {
				box->m_TilePos = vec2u(second.x, second.y);
				m_PushedBox = box;
				break;
			}
		}
	}

	return true;
}

Player::Player(TileMap* tile_map)
	: m_TileMap(tile_map)
{
	set_sprite("player-ss", 0, 0, 64, 64);
	set_scale(vec2f(1.5f, 1.5f));
	m_Animation = new Animation(this);
	m_Animation->load_sprite_sheet("player-ss");
	m_Animation->new_animation("MovingDown", 0, 0, 64, 64, 9);
	m_Animation->new_animation("MovingUp", 0, 64, 64, 64, 9);
	m_Animation->new_animation("MovingRight", 0, 128, 64, 64, 9);
	m_Animation->new_animation("MovingLeft", 0, 192, 64, 64, 9);
	animate(Standing);
}

Player::~Player()
{
	LOG_WARN("Player object deleted");
	delete m_Animation;
}
