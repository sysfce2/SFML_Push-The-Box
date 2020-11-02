#pragma once
#include "Entity.h"
#include "StatePlaying.h"
#include "Box.h"

class Player;

using vec2u = sf::Vector2u;

enum Tile : uint8_t {
	t_None = 0,
	t_Wall = 1,
	t_Box = 2
};

class TileMap
{
public:
	friend class StatePlaying;
	bool load_level(const std::string file_path);
	vec2f get_tile_size() const;
	Tile** get_map() const;

	TileMap();
	virtual ~TileMap();
private:
	void update(const float& dt);
	
	vec2u m_LevelSize = { 0, 0 };
	vec2f m_TileSize;
	std::vector<Entity*> m_Tiles;
	std::vector<Box*> m_Boxes;
	Tile** m_Map;
	Player* m_Player = nullptr;
};