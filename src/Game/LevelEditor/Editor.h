#pragma once
#include "State/State.h"
#include "UI/UIButton.h"
#include "UI/UICheckBox.h"
#include "Game/TileMap.h"

#define PLAYER_TILE 0xFF

class Tile;
class Tool;
class ToolBox;
struct Rect { vec2f pos; vec2f size; };

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
	static Tile* PlayerTile;
private:
	vec2f m_TileSize;
	vec2u m_LevelSize;
	std::string m_FileName;
	std::vector<std::vector<Tile*>> m_Tiles;
	
	UIElement* m_Canvas;
	UIElement* m_Background;
	UIText* m_HeaderText;
	ToolBox* m_ToolBox;
	UIButton* m_bSave;
	UIButton* m_bExit;
};

class Tile : public Entity
{
public:
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

class Tool : public UICheckBox
{
public:
	friend class ToolBox;
	Tool(uint8_t id, const std::string& sprite);
	virtual ~Tool() = default;
private:
	uint8_t m_TileId;
};

class ToolBox : public UIElement
{
public:
	ToolBox();
	virtual ~ToolBox() = default;
private:
	void update(const float& dt);
	UIText* m_tBoxCount;
	UIButton* m_BoxMinus;
	UIButton* m_BoxPlus;
	UIText* m_tTiles;
	UIText* m_tPlayer;
	std::vector<Tool*> m_Tools;
};