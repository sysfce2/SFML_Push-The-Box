#pragma once
#include "Tile.h"

class TileMap;

class Box : public Entity
{
public:
	friend class Player;
	bool m_CheckForStorage = true;
	bool m_IsOnStorage = false;
	Box(vec2f place_pos, vec2u tile_pos, TileMap* t_ptr);
	virtual ~Box() = default;
private:
	void update(const float& dt) override;
	TileMap* m_TileMap;
	vec2u m_TilePos;
};