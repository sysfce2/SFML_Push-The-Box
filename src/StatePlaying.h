#pragma once
#include "State.h"
#include "Player.h"
#include "Wall.h"

class StatePlaying : public State
{
private:
	void update(const float& dt);
public:
	StatePlaying();
	virtual ~StatePlaying();

private:
	const float m_CameraBorderDistance = 0.15f;
	Player* m_Player;
};