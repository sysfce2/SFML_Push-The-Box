#include "StateLevelSelect.h"
#include "EntityState/StatesManager.h"
#include "StatePlaying.h"
#include "Core/Window.h"
#include "Core/Logger.h"

vec2f def_scale = vec2f(2.f, 2.f);

SelectFrame::SelectFrame(const vec2f& position, bool completed, const std::string& type, uint16_t number)
	: UIElement(completed ? "completed" : "not-completed", def_scale)
{
	set_position(position);
	m_LevelNumber = new UIText(std::to_string(number), "invasion", 32);
	m_LevelNumber->attach_position(this);
	m_LevelNumber->set_position(vec2f(0.015f, 0.f));
	m_LevelNumber->center_y();
	if (completed)
		m_LevelNumber->set_color(sf::Color(105, 91, 0, 255));
	m_PlayButton = new UIButton("play-btn", def_scale);
	m_PlayButton->attach_position(this);
	m_PlayButton->set_position(vec2f(0.075f, 0.0f));
	m_PlayButton->center_y();
	m_LevelPath = "levels/" + type + "/" + type + std::to_string(number) + ".lvl";
	add_child_entity(m_LevelNumber);
	add_child_entity(m_PlayButton);
}

SelectFrame::~SelectFrame()
{
}

void StateLevelSelect::update(const float& dt)
{
	for (auto& b : m_Easy)
		if (b->m_PlayButton->was_pressed())
			StatesManager::create_active_state(new StatePlaying(b->m_LevelPath));

	if (back_button->was_pressed())
		destroy_state();
}

StateLevelSelect::StateLevelSelect()
{
	UIElement* state_background = new UIElement("select-state", vec2f(1.f, 1.f));
	make_entity(state_background);
	UIText* select_title = new UIText("WYBIERZ POZIOM", "joystix", 54);
	select_title->set_color(sf::Color(229, 198, 0, 255));
	select_title->set_position(vec2f(0.f, .03f));
	select_title->center_x();
	make_entity(select_title);

	SelectFrame* pattern = new SelectFrame(vec2f(0.f, 0.f), true, "easy", 1);
	vec2f pattern_size = pattern->get_size();
	vec2f place_offset = vec2f((1.f - pattern_size.x * 6.f) / 7.f, .03f);
	vec2f place_pos = vec2f(place_offset.x, .18f);
	
	for (uint16_t i = 0; i < 5; i++) {
		for (uint16_t j = 0; j < 6; j++) {
			uint16_t level_number = i * 6 + j + 1;
			bool completed = level_number == 1;
			SelectFrame* frame = new SelectFrame(place_pos, completed, "easy", level_number);
			m_Easy.emplace_back(frame);
			make_entity(frame);
			place_pos.x += place_offset.x + pattern_size.x;
		}
		place_pos.x = place_offset.x;
		place_pos.y += place_offset.y + pattern_size.y;
	}

	back_button = new UIButton(L"WRÓÆ", vec2f(3.f, 3.f), 48);
	back_button->set_position(vec2f(0.f, 0.85f));
	back_button->center_x();
	make_entity(back_button);
	delete pattern;
}

StateLevelSelect::~StateLevelSelect()
{
}

