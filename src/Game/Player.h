#pragma once
#include "Entity/Entity.h"
#include "TileMap.h"
#include "Tiles/Box.h"
#include "Entity/Animation.h"
#include <unordered_map>

struct PlayerControl
{
	bool go_up = false;
	bool go_down = false;
	bool go_right = false;
	bool go_left = false;
	inline static PlayerControl& get() {
		if (s_Instance == nullptr)
			s_Instance = new PlayerControl();
		return *s_Instance;
	}
	inline void reset();
private:
	static PlayerControl* s_Instance;
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
	void try_walk(vec2i direction, const std::string& animation);
	bool walk(vec2i offset, Box*& pushed_box);

	std::unique_ptr<Animation> m_Animation;
	TileMap* m_TileMap = nullptr;
	uint32_t* m_Moves = nullptr;
	vec2u m_TilePosition;
	bool m_StoppedWalking = true;
	float m_TileSize;
	float m_MovementSpeed = 300.f;
};