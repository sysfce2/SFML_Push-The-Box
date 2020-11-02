#pragma once
#include "Entity.h"
#include "TileMap.h"

enum Direction : uint8_t {
	Up = 1,
	Right = 2,
	Down = 3,
	Left = 4
};

enum AnimationState : uint8_t {
	Standing = 0,
	MovingUp = 1,
	MovingRight = 2,
	MovingDown = 3,
	MovingLeft = 4
};

class Player : public Entity
{
public:
	friend class TileMap;
	Player(TileMap* tile_map);
	virtual ~Player();
private:
	void update(const float& dt);
	void move(Direction direction);
	bool can_move(uint16_t tile_x, uint16_t tile_y);

	AnimationState m_AnimationState = Standing;
	TileMap* m_TileMap;
	vec2f m_DestinationPos;
	vec2u m_TilePosition;
	float m_MovementSpeed = 250.f;
};

