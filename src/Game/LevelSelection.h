#pragma once
#include "State/State.h"
#include "UI/ButtonUI.h"
#include "UI/TextUI.h"
#include "UI/SelectListUI.h"

class SelectBlock;
class CustomLevels;

class LevelSelection : public State {
public:
	friend class GamePlay;
	LevelSelection();
	virtual ~LevelSelection();

private:
	void update(const float& dt) override;

	static std::vector<SelectBlock*> m_Levels;
	ElementUI* m_Background;
	TextUI* m_HeaderText;
	ButtonUI* m_bBack;
	ButtonUI* m_bCustom;
	ButtonUI* m_bEditor;
};

class SelectBlock : public ElementUI
{
public:
	friend class LevelSelection;
	void refresh();
	SelectBlock(vec2f position, u16 number);
	virtual ~SelectBlock() = default;
private:
	ButtonUI* m_bPlay;
	TextUI* m_tNumber;
	TextUI* m_tTime;
	TextUI* m_tMoves;
	u16 m_Number;
};

class CustomLevelSelector
{
public:
	void create(State* owner_state, std::wstring action_btn_name, u16 add_to_layers = 0);
	bool action_was_pressed();
	std::string get_level_path();
	std::wstring get_level_name();

private:
	SelectListUI* m_LevelList;
	ButtonUI* m_bScrollUp;
	ButtonUI* m_bScrollDown;
	ButtonUI* m_bSelectAction;
};

class CustomLevels : public State
{
public:
	CustomLevels();

private:
	void update(const float& dt) override;
	CustomLevelSelector m_LevelSelector;

	ElementUI* m_Background;
	TextUI* m_HeaderText;
	ButtonUI* m_bBack;
};