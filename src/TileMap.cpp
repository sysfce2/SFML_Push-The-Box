#include "TileMap.h"
#include <fstream>
#include "Wall.h"
#include "Logger.h"
#include "Floor.h"
#include "Player.h"

bool TileMap::load_level(const std::string file_path)
{
	std::ifstream file(file_path);
	std::vector<Tile> tiles;

	if (file.is_open()) {
		std::string line;
		vec2f place_pos = { 0.f, 0.f };
		vec2u tile_pos = { 0, 0 };
		m_TileSize = Wall(place_pos).get_size_px();

		while (getline(file, line)) {
			LOG(line);
			for (const char& c : line) {
				if (c == '#') {
					m_Tiles.emplace_back(new Wall(place_pos));
					tiles.emplace_back(t_Wall);
				}
				else if (c == 'b') {
					TileBox tb = { new Box(place_pos), tile_pos };
					m_Boxes.emplace_back(tb);
					m_Tiles.emplace_back(new Floor(place_pos));
					tiles.emplace_back(t_Box);
				}
				else if (c == 'p') {
					if (m_Player == nullptr) {
						m_Player = new Player(this);
						vec2f offset = { (m_TileSize.x - m_Player->get_size_px().x) / 2,
							(m_TileSize.y - m_Player->get_size_px().y) / 2 };
						m_Player->set_position_px(vec2f(place_pos.x + offset.x, place_pos.y + offset.y));
						m_Player->m_DestinationPos = m_Player->get_position_px();
						m_Player->m_TilePosition = { tile_pos.x, tile_pos.y };
					}
					m_Tiles.emplace_back(new Floor(place_pos));
					tiles.emplace_back(t_None);
				}
				else {
					m_Tiles.emplace_back(new Floor(place_pos));
					tiles.emplace_back(t_None);
				}

				place_pos.x += m_TileSize.x;
				tile_pos.x++;
			}
			m_LevelSize.x = std::max(m_LevelSize.x, tile_pos.x);
			place_pos.x = 0.f;
			tile_pos.x = 0;
			place_pos.y += m_TileSize.y;
			tile_pos.y++;
		}
		m_LevelSize.y = tile_pos.y;

		file.close();

		if (m_Player == nullptr)
			return false;

		m_Map = new Tile * [m_LevelSize.x];
		for (size_t i = 0; i < m_LevelSize.x; i++) {
			m_Map[i] = new Tile[m_LevelSize.y];
			for (size_t j = 0; j < m_LevelSize.y; j++) {
				m_Map[i][j] = tiles.at(j * m_LevelSize.x + i);
			}
		}

		return true;
	}
	else return false;
}

vec2f TileMap::get_tile_size() const
{
	return m_TileSize;
}

TileMap::TileMap()
	: m_Map(nullptr)
{
}

TileMap::~TileMap()
{
}

void TileMap::update(const float& dt)
{
}
