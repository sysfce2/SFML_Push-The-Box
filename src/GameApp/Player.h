#pragma once
#include "EntityState/Entity.h"
#include "TileMap.h"
#include "Box.h"
#include "EntityState/Animation.h"

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
	void update(const float& dt) override;
	void move(Direction direction);
	void animate(AnimationState an_state);
	bool can_move(vec2i offset);

	uint8_t m_StandingWait = 0;
	AnimationState m_AnimationState = Standing;
	Animation* m_Animation = nullptr;
	TileMap* m_TileMap = nullptr;
	Box* m_PushedBox = nullptr;
	vec2f m_DestinationPos;
	vec2u m_TilePosition;
	float m_MovementSpeed = 300.f;
};

