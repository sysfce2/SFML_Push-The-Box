#pragma once
#include "State.h"
#include "UIElement.h"
#include "UIButton.h"

struct LevelSelectBox
{
	UIButton* play_button;
	std::string level_path;
};

class StateLevelSelect : public State {
private:
	void update(const float& dt) override;
	void make_level_btn(vec2f place_pos, const std::string& level_path);
public:
	StateLevelSelect();
	virtual ~StateLevelSelect();
private:
	std::vector<LevelSelectBox> m_Buttons;
	UIButton* back_button;
};