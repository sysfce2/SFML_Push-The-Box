#pragma once
#include "State.h"

class TileMap;
class Player;

class StatePlaying : public State
{
public:
	friend class TileMap;
private:
	void update(const float& dt) override;
public:
	StatePlaying(const std::string& level_path);
	virtual ~StatePlaying();

private:
	const float m_CameraBorderDistance = 0.4f;
	Player* m_Player;
	TileMap* m_TileMap;
};