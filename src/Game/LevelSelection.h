#pragma once
#include "State/State.h"
#include "UI/UIElement.h"
#include "UI/UIButton.h"
#include "UI/UIText.h"

class SelectFrame : public UIElement
{
public:
	friend class LevelSelection;
	SelectFrame(const vec2f& position, bool completed, const std::string& type, uint16_t number);
	virtual ~SelectFrame() = default;
private:
	UIButton* m_PlayButton;
	UIText* m_LevelNumber;
	std::string m_LevelPath;
};

using Levels = std::vector<SelectFrame*>;

class LevelSelection : public State {
private:
	void update(const float& dt) override;
public:
	LevelSelection();
	virtual ~LevelSelection() = default;
private:
	void switch_scene(uint8_t scene);

	uint8_t m_Scene = 0;
	Levels m_Easy;
	Levels m_Hard;
	Levels m_Expert;
	Levels* m_SelectedDifficulty = nullptr;

	UIButton* m_EasyButton;
	UIButton* m_HardButton;
	UIButton* m_ExpertButton;
	UIButton* m_BackButton;
	UIText* m_HeaderText;
};