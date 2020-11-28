#pragma once
#include "EntityState/Entity.h"
#include "StatePlaying.h"
#include "Box.h"

class Player;

enum Tile : uint8_t {
	t_None = 0,
	t_Wall = 1,
	t_Box = 2
};

class TileMap
{
public:
	friend class StatePlaying;
	bool load_level(const std::string& file_path);
	vec2f get_tile_size() const;
	Tile** m_Map;
	std::vector<Box*> m_Boxes;

	TileMap();
	virtual ~TileMap();
private:
	void update(const float& dt);
	
	uint16_t m_BoxesOnTargets = 0;
	vec2u m_LevelSize = { 0, 0 };
	vec2f m_TileSize;
	std::vector<Entity*> m_Tiles;
	std::vector<vec2u> m_Targets;
	Player* m_Player = nullptr;
};