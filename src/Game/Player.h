#pragma once
#include "Entity/Entity.h"
#include "TileMap.h"
#include "Box.h"
#include "Entity/Animation.h"
#include <unordered_map>

struct PlayerControl
{
	static bool go_up;
	static bool go_down;
	static bool go_right;
	static bool go_left;
};

class Player : public Entity
{
public:
	friend class GamePlay;
	friend class TileMap;
	Player(TileMap* tile_map);
	virtual ~Player() = default;
private:
	void update(const float& dt) override;
	void walk(vec2i direction, const std::string& animation);
	bool can_walk(vec2i offset);

	std::unique_ptr<Animation> m_Animation;
	TileMap* m_TileMap = nullptr;
	Box* m_PushedBox = nullptr;
	uint32_t* m_Moves = nullptr;
	vec2u m_TilePosition;
	uint16_t m_AnimationStopDelay = 0;
	float m_TileSize;
	float m_MovementSpeed = 300.f;
};