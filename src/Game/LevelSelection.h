#pragma once
#include "State/State.h"
#include "UI/ElementUI.h"
#include "UI/ButtonUI.h"
#include "UI/TextUI.h"

#define DIFFICULTY_SELECTION	LAYER_1
#define EASY_LEVELS				LAYER_2
#define HARD_LEVELS				LAYER_3
#define EXPERT_LEVELS			LAYER_4

class SelectBlock : public ElementUI
{
public:
	friend class LevelSelection;
	SelectBlock(const vec2f& position, uint16_t number);
	virtual ~SelectBlock() = default;
private:
	ButtonUI* m_PlayButton;
	TextUI* m_NumberText;
	uint16_t m_Number;
};

class LevelSelection : public State {
private:
	void update(const float& dt) override;
public:
	LevelSelection();
	virtual ~LevelSelection() = default;
private:
	void switch_layer(uint16_t layer);

	std::vector<SelectBlock*> m_Levels;
	ElementUI* m_Background;
	TextUI* m_HeaderText;
	ButtonUI* m_EasyButton;
	ButtonUI* m_HardButton;
	ButtonUI* m_ExpertButton;
	ButtonUI* m_BackButton;
	ButtonUI* m_EditorButton;
};