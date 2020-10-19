#pragma once
#include "Entity.h"
#include "StatePlaying.h"

struct Tile
{
	uint16_t tile_id;
	Entity* entity_ptr;
};

using vec2u = sf::Vector2u;

class TileMap
{
public:
	void load_level(const std::string file_path);

	TileMap(StatePlaying* state);
	virtual ~TileMap();
private:
	void update(const float& dt);
	
	vec2u m_LevelSize;
	std::vector<Tile> m_Tiles;
	StatePlaying* m_State;
};