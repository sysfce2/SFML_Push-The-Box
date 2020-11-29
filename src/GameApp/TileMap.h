#pragma once
#include "EntityState/Entity.h"
#include "GamePlay.h"
#include "Box.h"

class Player;

enum class Tile {
	None, Wall, Box
};

class TileMap
{
public:
	friend class GamePlay;
	friend class Player;
	bool load_level(const std::string& file_path);
	vec2f get_tile_size() const;

	TileMap() = default;
	virtual ~TileMap();
private:
	void update(const float& dt);

public:
	std::vector<Box*> m_Boxes;
	static uint16_t s_BoxesOnTargets;
	static std::vector<vec2u> s_Targets;
private:
	Tile** m_Map = nullptr;
	Player* m_Player = nullptr;
	vec2u m_LevelSize;
	vec2f m_TileSize;
	std::vector<Entity*> m_Tiles;
};