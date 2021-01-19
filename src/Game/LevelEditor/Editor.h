#pragma once
#include "State/State.h"
#include "UI/ButtonUI.h"
#include "UI/CheckBoxUI.h"
#include "Game/TileMap.h"

#define PLAYER_TILE 0xFF
#define ERASER 0xFD

class Tile;
class Tool;
class ToolBox;

class Editor : public State
{
private:
	void update(const float& dt) override;
	void save_level();
public:
	Editor(std::string file_name, vec2u size);
	virtual ~Editor() = default;

	static const Rect CanvasRect;
	static bool CameraChanged;
	static bool PlayerPlaced;
	static uint8_t SelectedTool;
	static uint16_t BoxesPlaced;
	static uint16_t StoragesPlaced;
	static uint16_t BoxesCount;
	static Tile* Player;
private:
	CameraInfo m_CameraInfo;
	vec2f m_TileSize;
	vec2u m_LevelSize;
	std::string m_FileName;
	std::vector<std::vector<Tile*>> m_Tiles;
	
	ElementUI* m_Canvas;
	ElementUI* m_Background;
	TextUI* m_HeaderText;
	ToolBox* m_ToolBox;
	ButtonUI* m_bSave;
	ButtonUI* m_bExit;
	TextUI* m_Info;
};

class Tile : public Entity
{
public:
	friend class Editor;
	Tile(vec2f* camera, vec2u tile_pos, uint8_t id = NONE_TILE);
	virtual ~Tile() = default;
private:
	void update(const float& dt) override;
	void select(bool selected = true);
	void set_tile(uint8_t tile_id);

	bool m_lMButtonReleased = true;
	bool m_rMButtonReleased = true;
	bool m_IsSelected = false;
	bool m_HasBox = false;
	bool m_HasStorage = false;
	bool m_HasPlayer = false;
	vec2f* m_CameraPtr;
	vec2u m_TilePos;
	uint8_t m_TileId;
};

class Tool : public CheckBoxUI
{
public:
	friend class ToolBox;
	Tool(uint8_t id, const std::string& sprite);
	virtual ~Tool() = default;
private:
	uint8_t m_TileId;
};

class ToolBox : public ElementUI
{
public:
	ToolBox();
	virtual ~ToolBox() = default;
private:
	void update(const float& dt);
	TextUI* m_tBoxCount;
	ButtonUI* m_BoxMinus;
	ButtonUI* m_BoxPlus;
	TextUI* m_tTiles;
	TextUI* m_tPlayer;
	std::vector<Tool*> m_Tools;
};

class OnSave : public State
{
	void update(const float& dt) override;
public:
	OnSave(std::wstring result, std::vector<std::wstring> info);
	virtual ~OnSave() = default;

private:
	ButtonUI* m_bBack;
};