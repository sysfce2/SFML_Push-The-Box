#pragma once
#include "State/State.h"
#include "UI/UIElement.h"
#include "UI/UIButton.h"
#include "UI/UIText.h"

#define DIFFICULTY_SELECTION	LAYER_1
#define EASY_LEVELS				LAYER_2
#define HARD_LEVELS				LAYER_3
#define EXPERT_LEVELS			LAYER_4

class SelectBlock : public UIElement
{
public:
	friend class LevelSelection;
	SelectBlock(const vec2f& position, uint16_t number);
	virtual ~SelectBlock() = default;
private:
	UIButton* m_PlayButton;
	UIText* m_NumberText;
	uint16_t m_Number;
};

using Levels = std::vector<SelectBlock*>;

class LevelSelection : public State {
private:
	void update(const float& dt) override;
public:
	LevelSelection();
	virtual ~LevelSelection() = default;
private:
	void switch_layer(uint16_t layer);

	Levels m_Levels;
	UIElement* m_Background;
	UIText* m_HeaderText;
	UIButton* m_EasyButton;
	UIButton* m_HardButton;
	UIButton* m_ExpertButton;
	UIButton* m_BackButton;
	UIButton* m_EditorButton;
};