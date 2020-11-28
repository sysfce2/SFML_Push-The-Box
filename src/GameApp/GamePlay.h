#pragma once
#include "EntityState/State.h"

class TileMap;
class Player;

class GamePlay : public State
{
public:
	friend class TileMap;
private:
	void update(const float& dt) override;
public:
	GamePlay(const std::string& level_path);
	virtual ~GamePlay();

private:
	const float m_CameraBorderDistance = 0.4f;
	Player* m_Player;
	TileMap* m_TileMap;
};