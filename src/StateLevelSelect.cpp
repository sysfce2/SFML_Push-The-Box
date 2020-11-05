#include "StateLevelSelect.h"
#include "StatesManager.h"
#include "StatePlaying.h"

void StateLevelSelect::update(const float& dt)
{
	for (const auto& b : m_Buttons)
		if (b.play_button->was_pressed())
			StatesManager::create_active_state(new StatePlaying(b.level_path));

	if (back_button->was_pressed())
		destroy_state();
}

void StateLevelSelect::make_level_btn(vec2f place_pos, const std::string& level_path)
{
	vec2f def_scale = vec2f(2.5f, 2.5f);
	UIElement* background = new UIElement("not-completed", def_scale);
	background->set_position(place_pos);
	UIButton* play_button = new UIButton("play-level-button", def_scale);
	play_button->set_position(vec2f(place_pos.x + 0.08f, 0.f));
	play_button->center_y(background);
	make_entity(background);
	make_entity(play_button);
	m_Buttons.emplace_back(LevelSelectBox{ play_button, level_path });

}

StateLevelSelect::StateLevelSelect()
{
	make_level_btn(vec2f(0.1f, 0.1f), "levels/test.level");
	back_button = new UIButton("back-button", vec2f(3.f, 3.f));
	back_button->set_position(vec2f(0.f, 0.85f));
	back_button->center_x();
	make_entity(back_button);
}

StateLevelSelect::~StateLevelSelect()
{
}
