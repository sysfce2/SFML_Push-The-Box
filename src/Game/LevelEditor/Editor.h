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
struct EditorValues;

class Editor : public State
{
private:
	void update(const float& dt) override;
	void save_level();

public:
	Editor(bool load_level, std::string file_path, vec2u size = vec2u());
	virtual ~Editor() = default;
	static EditorValues Values;

private:
	CameraInfo m_CameraInfo;
	vec2f m_TileSize;
	vec2u m_LevelSize;
	std::string m_FilePath;
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
	Tile(vec2f* camera, vec2u tile_pos, u8 id = NONE_TILE);
	virtual ~Tile() = default;
private:
	void update(const float& dt) override;
	void select(bool selected = true);
	void set_tile(u8 tile_id);

	bool m_lMButtonReleased = true;
	bool m_rMButtonReleased = true;
	bool m_IsSelected = false;
	bool m_HasBox = false;
	bool m_HasStorage = false;
	bool m_HasPlayer = false;
	vec2f* m_CameraPtr;
	vec2u m_TilePos;
	u8 m_TileId;
};

class Tool : public CheckBoxUI
{
public:
	friend class ToolBox;
	Tool(u8 id, const std::string& sprite);
	virtual ~Tool() = default;
private:
	u8 m_TileId;
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

struct EditorValues
{
	Rect canvas_rect;
	u16 boxes_placed;
	u16 storages_placed;
	u16 boxes_count;
	u8 selected_tool;
	Tile* player = nullptr;
	bool camera_changed;
	bool player_placed;

	void reset() {
		canvas_rect = { {.03f, .055f}, {.67f, .88f} };
		boxes_placed = 0;
		storages_placed = 0;
		boxes_count = 4;
		selected_tool = 1;
		player = nullptr;
		camera_changed = false;
		player_placed = false;
	}
};