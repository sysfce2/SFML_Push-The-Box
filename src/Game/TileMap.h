#pragma once
#include "Entity/Entity.h"
#include "GamePlay.h"
#include "Box.h"

#define FLOOR_FILE_ID	0
#define WALL_FILE_ID	1
#define BOX_FILE_ID		2
#define TARGET_FILE_ID	3

enum class Tile {
	None, Wall, Box
};

class Player;
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