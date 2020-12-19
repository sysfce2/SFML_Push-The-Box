#include "TileMap.h"
#include "Core/Logger.h"

#include <cstdlib>
#include <fstream>

bool TileMap::load_level(const std::string& file_path)
{
	std::ifstream file(file_path, std::ios_base::in | std::ios_base::binary);
	if (file.is_open()) {
		vec2u level_size;
		vec2u player_pos;
		vec2f place_pos;
		uint16_t storages_count;
		m_TileSize = Wall(vec2f(), vec2f(), 0).set_scale(m_TileScale).get_size_px().x;

		file.read(reinterpret_cast<char*>(&level_size), sizeof(vec2u));
		file.read(reinterpret_cast<char*>(&player_pos), sizeof(vec2u));
		file.read(reinterpret_cast<char*>(&storages_count), sizeof(uint16_t));

		m_BoxPlacePositions.reserve(storages_count);
		m_StoragePositions.reserve(storages_count);
		for (uint16_t i = 0; i < storages_count; i++) {
			vec2u storage_pos;
			file.read(reinterpret_cast<char*>(&storage_pos), sizeof(vec2u));
			m_StoragePositions.emplace_back(storage_pos);
		}

		m_Boxes.reserve(storages_count);
		m_Storages.reserve(storages_count);
		m_Tiles.reserve(level_size.x * level_size.y);
		m_Map.reserve(level_size.x);
		for (uint16_t i = 0; i < level_size.x; i++) {
			m_Map.emplace_back(std::vector<uint16_t>());
			m_Map.back().reserve(level_size.y);
			for (uint16_t j = 0; j < level_size.y; j++)
				m_Map.back().emplace_back(NONE_TILE);
		}

		uint16_t boxes_created = 0;
		for (uint16_t i = 0; i < level_size.x; i++) {
			for (uint16_t j = 0; j < level_size.y; j++) {

				uint8_t tile_id;
				uint8_t rand_int = rand() % 256;
				vec2u tile_pos{ i, j };
				vec2f place_pos{ m_TileSize * i, m_TileSize * j };
				file.read(reinterpret_cast<char*>(&tile_id), sizeof(uint8_t));

				if (tile_id == FLOOR_TILE) {
					Floor* floor = new Floor(place_pos, tile_pos, rand_int);
					m_Tiles.emplace_back(floor)->set_scale(m_TileScale);
					m_Map[i][j] = FLOOR_TILE;
				}
				else if (tile_id == WALL_TILE) {
					Wall* wall = new Wall(place_pos, tile_pos, rand_int);
					m_Tiles.emplace_back(wall)->set_scale(m_TileScale);
					m_Map[i][j] = WALL_TILE;
				}
				else if (tile_id == BOX_TILE) {
					Floor* floor = new Floor(place_pos, tile_pos, rand_int);
					m_Tiles.emplace_back(floor)->set_scale(m_TileScale);
					if (boxes_created < storages_count) {
						m_BoxPlacePositions.emplace_back(tile_pos);
						m_Map[i][j] = BOX_TILE;
						boxes_created++;
					}
					else m_Map[i][j] = FLOOR_TILE;
				}
				else if (tile_id == NONE_TILE) {
					m_Map[i][j] = NONE_TILE;
				}
				else {
					LOG_ERROR("Undefined tile id:", tile_id);
					return false;
				}
			}
		}
		
		for (vec2u s : m_StoragePositions) {
			vec2f pos = { (float)s.x * m_TileSize, (float)s.y * m_TileSize };
			Storage* storage = new Storage(pos, s);
			m_Storages.emplace_back(storage)->set_scale(m_TileScale);
		}

		for (vec2u b : m_BoxPlacePositions) {
			vec2f pos = { (float)b.x * m_TileSize, (float)b.y * m_TileSize };
			Box* box = new Box(pos, b, this);
			m_Boxes.emplace_back(box)->set_scale(m_TileScale);
		}

		m_Player = new Player(this);
		m_Player->set_scale(m_TileScale);
		vec2f offset = (vec2f(m_TileSize, m_TileSize) - m_Player->get_size_px()) / 2.f;
		vec2f place_px = (vec2f)player_pos * m_TileSize;
		m_Player->set_position_px(place_px + offset);
		m_Player->m_TilePosition = player_pos;
		m_LevelSize = level_size;
		file.close();
	}
	else return false;
	return true;
}

void TileMap::update(const float& dt)
{
}
