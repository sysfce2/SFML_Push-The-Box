#include "TileMap.h"
#include "Wall.h"
#include "Core/Logger.h"
#include "Floor.h"
#include "Player.h"
#include <cstdlib>
#include <time.h>
#include <fstream>

uint16_t TileMap::s_BoxesOnTargets;
std::vector<vec2u> TileMap::s_Targets;

bool TileMap::load_level(const std::string& file_path)
{
	std::ifstream size_check(file_path, std::ios_base::ate | std::ios_base::binary);
	uint32_t file_size = static_cast<uint32_t>(size_check.tellg());
	size_check.close();

	std::ifstream file(file_path, std::ios_base::in | std::ios_base::binary);
	if (file.is_open()) {
		vec2u level_size;
		vec2u player_pos;
		file.read(reinterpret_cast<char*>(&level_size), sizeof(vec2u));
		file.read(reinterpret_cast<char*>(&player_pos), sizeof(vec2u));
		if (level_size.x * level_size.y != file_size - sizeof(vec2u) * 2) return false;
		srand((unsigned)time(NULL));
		vec2f place_pos = { 0.f, 0.f };
		m_TileSize = Wall(place_pos, 0).get_size_px();
		m_Map = new Tile * [level_size.x];

		for (uint32_t i = 0; i < level_size.x; i++) {
			m_Map[i] = new Tile[level_size.y];
			for (uint32_t j = 0; j < level_size.y; j++) {
				uint8_t tile_type;
				uint8_t rand_int = rand() % 256;
				file.read(reinterpret_cast<char*>(&tile_type), sizeof(uint8_t));
				if (tile_type == 3) {
					m_Tiles.emplace_back(new Floor(place_pos, rand_int, true));
					s_Targets.emplace_back(vec2u(i, j));
					m_Map[i][j] = Tile::None;
				}
				else if (tile_type == 2) {
					m_Boxes.emplace_back(new Box(place_pos, { i, j }));
					m_Tiles.emplace_back(new Floor(place_pos, rand_int));
					m_Map[i][j] = Tile::Box;
				}
				else if (tile_type == 1) {
					m_Tiles.emplace_back(new Wall(place_pos, rand_int));
					m_Map[i][j] = Tile::Wall;
				}
				else if (tile_type == 0) {
					m_Tiles.emplace_back(new Floor(place_pos, rand_int));
					m_Map[i][j] = Tile::None;
				}
				else return false;
				place_pos.y += m_TileSize.y;
			}
			place_pos.x += m_TileSize.x;
			place_pos.y = 0;
		}

		m_Player = new Player(this);
		vec2f offset = (m_TileSize - m_Player->get_size_px()) / 2.f;
		vec2f place_px = (vec2f)player_pos * m_TileSize;
		m_Player->set_position_px(place_px + offset);
		m_Player->m_DestinationPos = m_Player->get_position_px();
		m_Player->m_TilePosition = player_pos;
		m_LevelSize = level_size;
		file.close();
	}
	else return false;
	return true;
}

vec2f TileMap::get_tile_size() const
{
	return m_TileSize;
}

TileMap::~TileMap()
{
	delete m_Map;
}

void TileMap::update(const float& dt)
{
}
