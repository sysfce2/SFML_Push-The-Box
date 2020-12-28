#pragma once
#include "State/State.h"
#include "UI/UIButton.h"
#include "UI/UITextBox.h"

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

	UIElement* m_Background;
	UIText* m_HeaderText;
	UIButton* m_bNew;
	UIButton* m_bLoad;
	UIButton* m_bBack;

	UITextBox* m_tbLevelName;
	UITextBox* m_tbLevelWidth;
	UITextBox* m_tbLevelHeight;
	UIButton* m_bCreate;
	UIText* m_NewCaption1;
	UIText* m_NewCaption2;
	UIText* m_NewCaption3;

	
};