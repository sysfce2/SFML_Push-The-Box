#pragma once
#include "Entity.h"
#include "StatePlaying.h"

using vec2u = sf::Vector2u;

class TileMap
{
public:
	friend class StatePlaying;
	void load_level(const std::string file_path);

	TileMap();
	virtual ~TileMap();
private:
	void update(const float& dt);
	
	vec2u m_LevelSize = { 0, 0 };
	std::vector<Entity*> m_Tiles;
};