#pragma once
#include "State/State.h"
#include "UI/UIButton.h"

class TileMap;
class Player;

class GamePlay : public State
{
public:
	friend class TileMap;
private:
	void update(const float& dt) override;
public:
	GamePlay(const std::string& level_path, const std::wstring& name = L"custom");
	virtual ~GamePlay() = default;

private:
	const float m_CameraBorderDistance = 0.4f;
	float m_fovWidth = 1.f;
	Player* m_Player = nullptr;
	TileMap* m_TileMap = nullptr;
	std::string m_LevelPath;
	std::wstring m_LevelNameStr;

	uint32_t m_Moves = 0;
	uint32_t m_PlayerMoves = 0;
	UIElement* m_Background = nullptr;
	UIElement* m_Menu = nullptr;
	UIText* m_LevelName = nullptr;
	UIText* m_MovesText = nullptr;
	UIButton* m_UndoButton = nullptr;
	UIButton* m_MoveUp = nullptr;
	UIButton* m_MoveDown = nullptr;
	UIButton* m_MoveRight = nullptr;
	UIButton* m_MoveLeft = nullptr;
	UIButton* m_Restart = nullptr;
	UIButton* m_Exit = nullptr;
};