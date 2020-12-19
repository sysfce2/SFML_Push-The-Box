#include "Player.h"
#include "Core/Logger.h"

constexpr uint16_t ANIMATION_FPS = 8;
PlayerControl* PlayerControl::s_Instance = nullptr;

void Player::update(const float& dt)
{
	update_movements(dt);
	m_Animation->update(dt);

	if (get_velocity_px().is_zero()) {

		if (!m_StoppedWalking) {
			m_StoppedWalking = true;
			m_Animation->stop();
		}

		if (PlayerControl::get().go_up)		try_walk({ 0, -1 }, "MovingUp");
		else if (PlayerControl::get().go_right)	try_walk({ 1, 0 },  "MovingRight");
		else if (PlayerControl::get().go_down)	try_walk({ 0, 1 },  "MovingDown");
		else if (PlayerControl::get().go_left)	try_walk({ -1, 0 }, "MovingLeft");
	}
}

void Player::try_walk(vec2i direction, const std::string& animation)
{
	Box* pushed_box = nullptr;
	if (walk(direction, pushed_box)) {

		vec2f movement = { m_TileSize * direction.x, m_TileSize * direction.y };
		start_movement(movement, m_MovementSpeed);

		m_Animation->play_animation(animation, ANIMATION_FPS, ANIMATE_REPEAT);
		m_TilePosition += direction;
		m_StoppedWalking = false;
		
		if (pushed_box != nullptr)
			pushed_box->start_movement(movement, m_MovementSpeed);
	}
}

bool Player::walk(vec2i offset, Box*& pushed_box)
{
	vec2i lsize = m_TileMap->m_LevelSize;
	vec2i first{ (int)m_TilePosition.x + offset.x , (int)m_TilePosition.y + offset.y };
	vec2i second{ (int)m_TilePosition.x + offset.x * 2, (int)m_TilePosition.y + offset.y * 2 };

	if (first.x < 0 || first.y < 0 || first.x >= lsize.x || first.y >= lsize.y)
		return false;

	if (m_TileMap->m_Map[first.x][first.y] == WALL_TILE
		|| m_TileMap->m_Map[first.x][first.y] == NONE_TILE)
		return false;

	if (m_TileMap->m_Map[first.x][first.y] == BOX_TILE) {
		
		if (second.x < 0 || second.y < 0 || second.x >= lsize.x || second.y >= lsize.y)
			return false;

		if (m_TileMap->m_Map[second.x][second.y] != FLOOR_TILE)
			return false;

		m_TileMap->m_Map[first.x][first.y] = FLOOR_TILE;
		m_TileMap->m_Map[second.x][second.y] = BOX_TILE;

		for (Box* box : m_TileMap->m_Boxes)
			if (box->m_TilePos == vec2u(first.x, first.y)) {
				box->m_TilePos = { (unsigned)second.x, (unsigned)second.y };
				box->m_CheckForStorage = true;
				pushed_box = box;
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
	PlayerControl::get().reset();
}

inline void PlayerControl::reset()
{
	go_up = false;
	go_down = false;
	go_right = false;
	go_left = false;
}
