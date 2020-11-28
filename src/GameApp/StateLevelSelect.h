#pragma once
#include "EntityState/State.h"
#include "UI/UIElement.h"
#include "UI/UIButton.h"
#include "UI/UIText.h"

class SelectFrame : public UIElement
{
public:
	friend class StateLevelSelect;
	SelectFrame(const vec2f& position, bool completed, const std::string& type, uint16_t number);
	virtual ~SelectFrame();
private:
	UIButton* m_PlayButton;
	UIText* m_LevelNumber;
	std::string m_LevelPath;
};

class StateLevelSelect : public State {
private:
	void update(const float& dt) override;
public:
	StateLevelSelect();
	virtual ~StateLevelSelect();
private:
	std::vector<SelectFrame*> m_Easy;
	vec2f m_SelectFormSize;
	UIButton* back_button;
};