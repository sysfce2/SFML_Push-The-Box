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
	GamePlay(const std::string& level_path, i32 number = -1, const std::wstring name = L"");
	virtual ~GamePlay() = default;

private:
	void update(const float& dt) override;

private:
	void construct_tilemap();

	CameraInfo m_CameraInfo;
	const float m_Border = 0.4f;
	float m_fovWidth = 1.f;
	Player* m_Player = nullptr;
	TileMap* m_TileMap = nullptr;
	std::vector<Undo> m_UndoRegister;
	std::string m_LevelPath;
	i32 m_LevelNumber = -1;
	u32 m_Moves = 0;
	u32 m_PlayerMoves = 0;
	u32 m_ElapsedTotal = 0;
	u32 m_ElapsedMinutes = 0;
	u32 m_ElapsedSeconds = 0;
	u32 m_AvaliableUndos = 0;
	float m_ElapsedTime = 0.f;
	bool m_LevelFinished = false;
	bool m_FlickState = false;
	u32 m_Flicks = 0;


	// Menu UI
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