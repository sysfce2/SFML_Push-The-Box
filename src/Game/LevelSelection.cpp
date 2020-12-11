#include "LevelSelection.h"
#include "GamePlay.h"
#include "State/StatesManager.h"
#include "Core/Window.h"
#include "Core/Logger.h"

const sf::Color GOLDEN_BROWN{ 105, 91, 0, 255 };
const sf::Color HEADER_COLOR{ 229, 198, 0, 255 };
const vec2f DEFAULT_SCALE{ 2.f, 2.f };

SelectFrame::SelectFrame(const vec2f& position, bool completed, const std::string& type, uint16_t number)
	: UIElement(completed ? "completed" : "not-completed", DEFAULT_SCALE)
{
	set_position(position);
	m_LevelNumber = new UIText(std::to_string(number), "invasion", 32);
	m_LevelNumber->attach_position(this).set_position({ 0.015f, 0.f }).center_y();
	if(completed) m_LevelNumber->set_color(GOLDEN_BROWN);

	m_PlayButton = new UIButton("", DEFAULT_SCALE);
	m_PlayButton->assign_sprite("play-btn", "play-btn-pressed");
	m_PlayButton->attach_position(this).set_position({ 0.075f, 0.0f }).center_y();

	m_LevelPath = "levels/" + type + "/" + type + "_" + std::to_string(number) + ".lvl";
	add_child_entity(m_LevelNumber);
	add_child_entity(m_PlayButton);
}

void LevelSelection::update(const float& dt)
{
	if (m_Scene == 0) {
		if (m_EasyButton->was_pressed()) {
			m_SelectedDifficulty = &m_Easy;
			switch_scene(1);
		}
		else if (m_HardButton->was_pressed()) {
			m_SelectedDifficulty = &m_Hard;
			switch_scene(2);
		}
		else if (m_ExpertButton->was_pressed()) {
			m_SelectedDifficulty = &m_Expert;
			switch_scene(3);
		}
	}
	else {
		for (auto& b : *m_SelectedDifficulty) if (b->m_PlayButton->was_pressed())
			StatesManager::get().create_active_state(new GamePlay(b->m_LevelPath));
	}

	if (m_BackButton->was_pressed()) {
		if (m_Scene > 0)
			switch_scene(0);
		else
			destroy_state();
	}
}

LevelSelection::LevelSelection()
{
	make_entity(new UIElement("select-state", { 1.f, 1.f }));

	m_HeaderText = new UIText(L"WYBIERZ POZIOM", "joystix", 54);
	m_HeaderText->set_color(HEADER_COLOR);
	m_HeaderText->set_position({ 0.f, .03f }).center_x();
	make_entity(m_HeaderText);

	m_EasyButton = new UIButton(L"£ATWE", { 3.f, 3.f }, 42);
	m_EasyButton->set_position({ 0.f, .2f }).center_x();
	make_entity(m_EasyButton);

	m_HardButton = new UIButton(L"TRUDNE", { 3.f, 3.f }, 42);
	m_HardButton->set_position({ 0.f, .35f }).center_x();
	make_entity(m_HardButton);

	m_ExpertButton = new UIButton(L"EKSPERT", { 3.f, 3.f }, 42);
	m_ExpertButton->set_position({ 0.f, .5f }).center_x();
	make_entity(m_ExpertButton);

	SelectFrame* frame = new SelectFrame({ 0.f, 0.f }, true, "easy", 1);
	vec2f frame_size = frame->get_size();
	vec2f place_offset = { (1.f - frame_size.x * 6.f) / 7.f, .03f };
	vec2f place_pos = { place_offset.x, .18f };
	delete frame;

	for (uint16_t i = 0; i < 5; i++) {
		for (uint16_t j = 0; j < 6; j++) {
			uint16_t level_number = i * 6 + j + 1;
			bool completed = level_number == 1;

			frame = new SelectFrame(place_pos, completed, "easy", level_number);
			frame->vanish(true);
			m_Easy.emplace_back(frame);
			make_entity(frame);

			frame = new SelectFrame(place_pos, completed, "hard", level_number);
			frame->vanish(true);
			m_Hard.emplace_back(frame);
			make_entity(frame);

			frame = new SelectFrame(place_pos, completed, "expert", level_number);
			frame->vanish(true);
			m_Expert.emplace_back(frame);
			make_entity(frame);

			place_pos.x += place_offset.x + frame_size.x;
		}
		place_pos.x = place_offset.x;
		place_pos.y += place_offset.y + frame_size.y;
	}

	m_BackButton = new UIButton(L"WRÓÆ", { 3.f, 3.f }, 42);
	m_BackButton->set_position({ 0.f, 0.85f }).center_x();
	make_entity(m_BackButton);
}

void LevelSelection::switch_scene(uint8_t scene)
{
	m_Scene = scene;
	std::wstring header_text;
	switch (scene) {
	case 0:
		header_text = L"WYBIERZ POZIOM";
		break;
	case 1:
		header_text = L"POZIOM £ATWY";
		break;
	case 2:
		header_text = L"POZIOM TRUDNY";
		break;
	case 3:
		header_text = L"POZIOM EKSPERT";
		break;
	}

	m_HeaderText->set_text(header_text);
	m_HeaderText->set_color(HEADER_COLOR);
	m_HeaderText->center_x();

	if (scene > 0) {
		m_EasyButton->vanish(true);
		m_HardButton->vanish(true);
		m_ExpertButton->vanish(true);
		for (auto& b : *m_SelectedDifficulty)
			b->appear();
	}
	else {
		m_EasyButton->appear();
		m_HardButton->appear();
		m_ExpertButton->appear();
		for (auto& b : *m_SelectedDifficulty)
			b->vanish(true);
	}
}
