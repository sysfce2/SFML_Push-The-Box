#include "TileMap.h"
#include <fstream>

void TileMap::load_level(const std::string file_path)
{
	std::ifstream file(file_path);



	file.close();
}

TileMap::TileMap(StatePlaying * state)
	: m_State(state)
{
}

TileMap::~TileMap()
{
}

void TileMap::update(const float& dt)
{
}
