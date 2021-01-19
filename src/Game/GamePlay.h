#pragma once
#include "State/State.h"
#include "UI/ButtonUI.h"
#include "Player.h"
#include "TileMap.h"

class GamePlay : public State
{
public:
	friend class TileMap;
	friend class GameCamera;
	GamePlay(const std::string& level_path, const std::wstring& name = L"???");
	virtual ~GamePlay() = default;

private:
	void update(const float& dt) override;

private:
	void construct_tilemap();

	CameraInfo m_CameraInfo;
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
	ElementUI* m_Background = nullptr;
	ElementUI* m_Menu = nullptr;
	TextUI* m_LevelName = nullptr;
	TextUI* m_Timer = nullptr;
	TextUI* m_MovesText = nullptr;
	TextUI* m_UndosText = nullptr;
	ButtonUI* m_UndoButton = nullptr;
	ButtonUI* m_MoveUp = nullptr;
	ButtonUI* m_MoveDown = nullptr;
	ButtonUI* m_MoveRight = nullptr;
	ButtonUI* m_MoveLeft = nullptr;
	ButtonUI* m_Restart = nullptr;
	ButtonUI* m_Exit = nullptr;
};