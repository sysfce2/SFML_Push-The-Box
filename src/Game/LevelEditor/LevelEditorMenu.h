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
public:
	LevelEditorMenu();
	virtual ~LevelEditorMenu() = default;
private:

	UIElement* m_Background;
	UIText* m_HeaderText;
	UIButton* m_NewButton;
	UIButton* m_LoadButton;
	UIButton* m_BackButton;
	UITextBox* m_LevelName;
	
};