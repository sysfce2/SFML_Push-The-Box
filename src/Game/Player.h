#pragma once
#include "Entity/Entity.h"
#include "TileMap.h"
#include "Tiles/Box.h"
#include "Entity/Animation.h"

constexpr u16 UNDOS_LIMIT = 10u;

struct PlayerControl
{
	bool go_up = false; bool go_down = false;
	bool go_right = false; bool go_left = false;

	inline static PlayerControl& get() {
		if (s_Instance == nullptr)
			s_Instance = new PlayerControl();
		return *s_Instance;
	}
	inline void reset() {
		go_up = false;  go_down = false;
		go_right = false; go_left = false;
	};
	inline u8 whole_state() {
		return (go_up << 3) + (go_down << 2) + (go_right << 1) + go_left;
	}
private:
	static PlayerControl* s_Instance;
};

struct Undo
{
	vec2i m_LastMove;
	std::string m_Animation;
	Box* m_Box = nullptr;
};

class Player : public Entity
{
public:
	friend class GamePlay;
	friend class TileMap;
	Player();
	virtual ~Player() = default;

private:
	void init(TileMap* tile_map, std::vector<Undo>* reg, u32* moves);
	void update(const float& dt) override;
	void try_walk(vec2i direction, const std::string& animation);
	bool walk(vec2i offset, Box*& pushed_box);

	std::vector<Undo>* m_UndoRegister;
	std::unique_ptr<Animation> m_Animation;
	TileMap* m_TileMap = nullptr;
	u32* m_Moves = nullptr;
	vec2u m_TilePosition;
	u8 m_PrevControlState = 0;
	float m_TileSize;
	float m_MovementSpeed = 300.f;
};