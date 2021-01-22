#pragma once
#include "State/State.h"
#include "UI/ElementUI.h"
#include "UI/ButtonUI.h"
#include "UI/TextUI.h"

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