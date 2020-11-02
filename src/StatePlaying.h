#pragma once
#include "State.h"

class TileMap;
class Player;

class StatePlaying : public State
{
public:
	friend class TileMap;
private:
	void update(const float& dt);
public:
	StatePlaying();
	virtual ~StatePlaying();

private:
	const float m_CameraBorderDistance = 0.25f;
	Player* m_Player;
	TileMap* m_TileMap;
};