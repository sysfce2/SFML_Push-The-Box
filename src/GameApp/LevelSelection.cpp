#include "LevelSelection.h"
#include "GamePlay.h"
#include "EntityState/StatesManager.h"
#include "Core/Window.h"
#include "Core/Logger.h"

const sf::Color GOLD{ 105, 91, 0, 255 };
const sf::Color HEADER_COLOR{ 229, 198, 0, 255 };
const vec2f DEFAULT_SCALE{ 2.f, 2.f };

SelectFrame::SelectFrame(const vec2f& position, bool completed, const std::string& type, uint16_t number)
	: UIElement(completed ? "completed" : "not-completed", DEFAULT_SCALE)
{
	set_position(position);
	m_LevelNumber = new UIText(std::to_string(number), "invasion", 32);
	m_LevelNumber->attach_position(this).set_position(vec2f(0.015f, 0.f)).center_y();
	m_PlayButton = new UIButton("play-btn", DEFAULT_SCALE);
	m_PlayButton->attach_position(this).set_position(vec2f(0.075f, 0.0f)).center_y();
	m_LevelPath = "levels/" + type + "/" + type + std::to_string(number) + ".lvl";
	if (completed) m_LevelNumber->set_color(sf::Color(105, 91, 0, 255));
	add_child_entity(m_LevelNumber);
	add_child_entity(m_PlayButton);
}

void LevelSelection::update(const float& dt)
{
	for (auto& b : m_Easy)
		if (b->m_PlayButton->was_pressed())
			StatesManager::get().create_active_state(new GamePlay(b->m_LevelPath));

	if (back_button->was_pressed())
		destroy_state();
}

LevelSelection::LevelSelection()
{
	UIElement* state_background = new UIElement("select-state", vec2f(1.f, 1.f));
	make_entity(state_background);
	UIText* select_title = new UIText("WYBIERZ POZIOM", "joystix", 54);
	select_title->set_color(HEADER_COLOR);
	select_title->set_position(vec2f(0.f, .03f)).center_x();
	make_entity(select_title);

	SelectFrame* frame = new SelectFrame(vec2f(0.f, 0.f), true, "easy", 1);
	vec2f frame_size = frame->get_size();
	vec2f place_offset = vec2f((1.f - frame_size.x * 6.f) / 7.f, .03f);
	vec2f place_pos = vec2f(place_offset.x, .18f);

	for (uint16_t i = 0; i < 5; i++) {
		for (uint16_t j = 0; j < 6; j++) {
			uint16_t level_number = i * 6 + j + 1;
			bool completed = level_number == 1;
			frame = new SelectFrame(place_pos, completed, "easy", level_number);
			m_Easy.emplace_back(frame);
			make_entity(frame);
			place_pos.x += place_offset.x + frame_size.x;
		}
		place_pos.x = place_offset.x;
		place_pos.y += place_offset.y + frame_size.y;
	}

	back_button = new UIButton(L"WRÓÆ", vec2f(3.f, 3.f), 48);
	back_button->set_position(vec2f(0.f, 0.85f)).center_x();
	make_entity(back_button);
}
