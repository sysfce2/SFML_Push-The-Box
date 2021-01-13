#pragma once
#include "State/State.h"
#include "UI/UIButton.h"
#include "Player.h"
#include "TileMap.h"

class GamePlay : public State
{
public:
	friend class TileMap;
	GamePlay(const std::string& level_path, const std::wstring& name = L"???");
	virtual ~GamePlay() = default;

private:
	void update(const float& dt) override;

private:
	void construct_tilemap();

	const float m_CameraBorderDistance = 0.4f;
	float m_fovWidth = 1.f;
	Player* m_Player = nullptr;
	TileMap* m_TileMap = nullptr;
	uint32_t m_Moves = 0;
	uint32_t m_PlayerMoves = 0;
	std::string m_LevelPath;
	std::wstring m_LevelNameStr;
	std::vector<Undo> m_UndoRegister;

	float m_ElapsedTime = 0.f;
	uint32_t m_ElapsedMinutes = 0u;
	uint32_t m_ElapsedSeconds = 0u;
	uint32_t m_AvaliableUndos = 0u;
	UIElement* m_Background = nullptr;
	UIElement* m_Menu = nullptr;
	UIText* m_LevelName = nullptr;
	UIText* m_Timer = nullptr;
	UIText* m_MovesText = nullptr;
	UIText* m_UndosText = nullptr;
	UIButton* m_UndoButton = nullptr;
	UIButton* m_MoveUp = nullptr;
	UIButton* m_MoveDown = nullptr;
	UIButton* m_MoveRight = nullptr;
	UIButton* m_MoveLeft = nullptr;
	UIButton* m_Restart = nullptr;
	UIButton* m_Exit = nullptr;
};