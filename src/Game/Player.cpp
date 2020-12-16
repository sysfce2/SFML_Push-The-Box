#include "Player.h"
#include "Core/Logger.h"

using KB = sf::Keyboard;
constexpr uint16_t ANIMATION_FPS = 8;
bool PlayerControl::go_up = false;
bool PlayerControl::go_down = false;
bool PlayerControl::go_right = false;
bool PlayerControl::go_left = false;

void Player::update(const float& dt)
{
	update_movements(dt);
	m_Animation->update(dt);

	vec2f velocity = get_velocity_px();
	if (velocity.x == 0.f && velocity.y == 0.f) {

		if (m_PushedBox != nullptr) {
			m_PushedBox->m_CheckForTarget = true;
			m_PushedBox = nullptr;
		}
		if (m_AnimationStopDelay++)
			m_Animation->stop();

		if (PlayerControl::go_up)
			walk({ 0, -1 }, "MovingUp");
		else if (PlayerControl::go_right)
			walk({ 1, 0 }, "MovingRight");
		else if (PlayerControl::go_down)
			walk({ 0, 1 }, "MovingDown");
		else if (PlayerControl::go_left)
			walk({ -1, 0 }, "MovingLeft");
	}
}

void Player::walk(vec2i direction, const std::string& animation)
{
	if (can_walk(direction)) {
		m_AnimationStopDelay = 0;
		m_Animation->play_animation(animation, ANIMATION_FPS, ANIMATE_REPEAT);
		vec2f movement = { m_TileSize * direction.x, m_TileSize* direction.y };
		start_movement(movement, m_MovementSpeed);
		m_TilePosition += direction;
		if (m_PushedBox != nullptr)
			m_PushedBox->start_movement(movement, m_MovementSpeed);
	}
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
	if (m_Moves != nullptr)
		(*m_Moves)++;
	return true;
}

Player::Player(TileMap* tile_map) : m_TileMap(tile_map)
{
	set_sprite("player-sprite-sheet", { 0, 0 }, { 64, 64 });
	m_TileSize = m_TileMap->get_tile_size();
	m_MovementSpeed *= get_scale().x;
	m_Animation = std::unique_ptr<Animation>(new Animation(this));
	m_Animation->set_sprite_sheet("player-sprite-sheet");
	m_Animation->new_animation("MovingDown", 0, 0, 64, 64, 9);
	m_Animation->new_animation("MovingUp", 0, 64, 64, 64, 9);
	m_Animation->new_animation("MovingRight", 0, 128, 64, 64, 9);
	m_Animation->new_animation("MovingLeft", 0, 192, 64, 64, 9);
}