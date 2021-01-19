#pragma once
#include "State/State.h"
#include "UI/ButtonUI.h"
#include "UI/TextBoxUI.h"

#define LE_MENU LAYER_1
#define LE_NEW LAYER_2
#define LE_LOAD LAYER_3

class LevelEditorMenu : public State
{
private:
	void update(const float& dt) override;
	bool create_level();
public:
	LevelEditorMenu();
	virtual ~LevelEditorMenu() = default;
private:

	ElementUI* m_Background;
	TextUI* m_HeaderText;
	ButtonUI* m_bNew;
	ButtonUI* m_bLoad;
	ButtonUI* m_bBack;

	TextBoxUI* m_tbLevelName;
	TextBoxUI* m_tbLevelWidth;
	TextBoxUI* m_tbLevelHeight;
	ButtonUI* m_bCreate;
	TextUI* m_NewCaption1;
	TextUI* m_NewCaption2;
	TextUI* m_NewCaption3;

	
};