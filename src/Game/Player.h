#pragma once
#include "Entity/Entity.h"
#include "TileMap.h"
#include "Box.h"
#include "Entity/Animation.h"
#include <unordered_map>

enum class Direction {
	Up, Right, Down, Left
};

enum class AnState {
	Standing, MovingUp, MovingRight, MovingDown, MovingLeft
};

struct PlayerControl
{
	static bool up_pressed;
	static bool down_pressed;
	static bool right_pressed;
	static bool left_pressed;
};

class Player : public Entity
{
public:
	friend class GamePlay;
	friend class TileMap;
	Player(TileMap* tile_map);
	virtual ~Player();
private:
	void update(const float& dt) override;
	void walk(Direction direction);
	void animate(AnState an_state);
	bool can_walk(vec2i offset);
	void set_moves_ptr(uint32_t* moves_ptr);

	bool m_StopWalking = true;
	std::unordered_map<AnState, std::string> m_AnName;
	AnState m_AnimationState = AnState::Standing;
	Animation* m_Animation = nullptr;
	TileMap* m_TileMap = nullptr;
	Box* m_PushedBox = nullptr;
	uint32_t* m_Moves = nullptr;
	vec2f m_DestinationPos;
	vec2u m_TilePosition;
	float m_MovementSpeed = 300.f;
};