#pragma once
#include "Entity.h"
#include "TileMap.h"
#include "Box.h"

using vec2i = sf::Vector2i;

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
	bool can_move(vec2i offset);

	AnimationState m_AnimationState = Standing;
	TileMap* m_TileMap;
	Box* m_PushedBox = nullptr;
	vec2f m_DestinationPos;
	vec2u m_TilePosition;
	float m_MovementSpeed = 250.f;
};

