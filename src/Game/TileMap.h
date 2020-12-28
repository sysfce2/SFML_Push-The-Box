#pragma once
#include "Player.h"
#include "Tiles/Floor.h"
#include "Tiles/Wall.h"
#include "Tiles/Box.h"
#include "Tiles/Storage.h"

#define NONE_TILE		0
#define FLOOR_TILE		1
#define WALL_TILE		2
#define BOX_TILE		3
#define STORAGE_TILE	4

class TileMap
{
public:
	friend class GamePlay;
	friend class Player;
	friend class Box;
	inline float get_tile_size() const { return m_TileSize; }
	bool load_level(const std::string& file_path);
private:
	void update(const float& dt);

private:
	std::vector<Entity*> m_Tiles;
	std::vector<Box*> m_Boxes;
	std::vector<Storage*> m_Storages;
	std::vector<vec2u> m_BoxPlacePositions;
	std::vector<vec2u> m_StoragePositions;
	std::vector<std::vector<uint16_t>> m_Map;
	uint16_t m_StoragesFilled = 0;
	Player* m_Player = nullptr;
	vec2u m_LevelSize;
	vec2f m_TileScale = { 1.1f, 1.1f };
	float m_TileSize = 32.f;
	
};