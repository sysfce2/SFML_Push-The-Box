#include "TileMap.h"
#include <fstream>
#include "Wall.h"
#include "Logger.h"
#include "Box.h"

void TileMap::load_level(const std::string file_path)
{
	std::ifstream file(file_path);
	if (file.is_open()) {
		std::string line;
		vec2f place_pos(0.f, 0.f);
		Wall* wall = new Wall({ 0.f, 0.f });
		Wall* free_n0 = wall;

		while (getline(file, line)) {
			LOG(line);
			for (const char& c : line) {
				if (c == '#') {
					wall = new Wall(place_pos);
					m_Tiles.push_back(wall);
				}
				else if (c == 'b') {
					m_Tiles.push_back(new Box(place_pos));
				}
				place_pos.x += wall->get_size_px().x;
				m_LevelSize.x++;
			}
			place_pos.x = 0.f;
			place_pos.y += wall->get_size_px().y;
			m_LevelSize.y++;
		}

		delete free_n0;
	}

	file.close();
}

TileMap::TileMap()
{
}

TileMap::~TileMap()
{
}

void TileMap::update(const float& dt)
{
}
