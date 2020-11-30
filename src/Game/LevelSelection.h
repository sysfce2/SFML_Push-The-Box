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

class LevelSelection : public State {
private:
	void update(const float& dt) override;
public:
	LevelSelection();
	virtual ~LevelSelection() = default;
private:
	std::vector<SelectFrame*> m_Easy;
	vec2f m_SelectFormSize;
	UIButton* back_button;
};