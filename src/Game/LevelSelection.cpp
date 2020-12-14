#include "State/StatesManager.h"
#include "Core/Window.h"
#include "Core/Logger.h"

#include "LevelSelection.h"
#include "GamePlay.h"
#include "LevelEditor/LevelEditorMenu.h"

const sf::Color GOLDEN_BROWN{ 105, 91, 0, 255 };
const sf::Color HEADER_COLOR{ 229, 198, 0, 255 };
const vec2f HEADER_POS = { 0.f, .03f };
const vec2f SELECT_BLOCK_SCALE{ 2.f, 2.f };
const vec2f BTN_SCALE{ 3.f, 3.f };
const uint8_t BTN_FNT_SIZE = 42;

SelectBlock::SelectBlock(const vec2f& position, uint16_t number)
	: UIElement("not-completed", SELECT_BLOCK_SCALE, position), m_Number(number)
{
	m_NumberText = new UIText(std::to_string(number), "invasion", 32);
	m_PlayButton = new UIButton("", SELECT_BLOCK_SCALE);
	m_PlayButton->assign_button_sprite("play-btn", "play-btn-pressed");
	m_NumberText->attach_position(this).set_position({ 0.015f, 0.f }).center_y();
	m_PlayButton->attach_position(this).set_position({ 0.075f, 0.0f }).center_y();
	add_child_entity(m_NumberText);
	add_child_entity(m_PlayButton);
}

void LevelSelection::update(const float& dt)
{
	uint16_t active_layer = layer_id();
	if (active_layer == DIFFICULTY_SELECTION) {
		if (m_EasyButton->was_pressed())	switch_layer(EASY_LEVELS);
		else if (m_HardButton->was_pressed())	switch_layer(HARD_LEVELS);
		else if (m_ExpertButton->was_pressed()) switch_layer(EXPERT_LEVELS);
		else if (m_EditorButton->was_pressed())
			StatesManager::get().create_active_state(new LevelEditorMenu());
	}
	else 
		for (auto& b : m_Levels) if (b->m_PlayButton->was_pressed()) {
			std::string type; std::wstring name;
			if (active_layer == EASY_LEVELS) {
				type = "easy";
				name = L"£ATWY";
			}
			else if (active_layer == HARD_LEVELS) {
				type = "hard";
				name = L"TRUDNY";
			}
			else if (active_layer == EXPERT_LEVELS) {
				type = "expert";
				name = L"EKSPERT";
			}
			std::string level_path = "levels/" + type + "/";
			level_path += type + "_" + std::to_string(b->m_Number) + ".lvl";
			name += L" - " + std::to_wstring(b->m_Number);
			StatesManager::get().create_active_state(new GamePlay(level_path, name));
		}

	if (m_BackButton->was_pressed())
		if (active_layer != DIFFICULTY_SELECTION)
			switch_layer(DIFFICULTY_SELECTION);
		else destroy_state();
}

LevelSelection::LevelSelection()
{
	vec2f btn_pos{ 0.f, 0.2f };
	vec2f pos_off{ 0.f, 0.15f };
	
	m_Background = new UIElement("select-state", { 1.f, 1.f });
	m_HeaderText = new UIText(L"WYBIERZ POZIOM", "joystix", 54);
	m_EasyButton = new UIButton(L"£ATWE", BTN_SCALE, BTN_FNT_SIZE);
	m_HardButton = new UIButton(L"TRUDNE", BTN_SCALE, BTN_FNT_SIZE);
	m_ExpertButton = new UIButton(L"EKSPERT", BTN_SCALE, BTN_FNT_SIZE);
	m_EditorButton = new UIButton(L"   EDYTOR\n   POZIOMóW", BTN_SCALE, 25);
	m_BackButton = new UIButton(L"WRÓÆ", BTN_SCALE, BTN_FNT_SIZE);

	m_HeaderText->set_color(HEADER_COLOR);
	m_HeaderText->set_position(HEADER_POS).center_x();
	m_EasyButton->set_position(btn_pos).center_x();
	m_HardButton->set_position(btn_pos + pos_off).center_x();
	m_ExpertButton->set_position(btn_pos + pos_off * 2).center_x();
	m_EditorButton->set_position({ 0.72f, 0.85f });
	m_BackButton->set_position({ 0.f, 0.85f }).center_x();
	m_EditorButton->assign_button_sprite("editor-btn", "editor-btn-pressed");
	
	make_entity(m_Background);
	make_entity(m_HeaderText);
	make_entity(m_EasyButton, DIFFICULTY_SELECTION);
	make_entity(m_HardButton, DIFFICULTY_SELECTION);
	make_entity(m_ExpertButton, DIFFICULTY_SELECTION);
	make_entity(m_EditorButton, DIFFICULTY_SELECTION);
	make_entity(m_BackButton);

	SelectBlock* block = new SelectBlock({ 0.f, 0.f }, 1);
	vec2f block_size =	block->get_size();
	vec2f place_offset = { (1.f - block_size.x * 6.f) / 7.f, .03f };
	vec2f place_pos = { place_offset.x, .18f };
	delete block;

	uint16_t rows = 5; uint16_t cols = 6;
	for (uint16_t i = 0; i < rows; i++) {
		for (uint16_t j = 0; j < cols; j++) {
			uint16_t level_number = i * 6 + j + 1;
			block = new SelectBlock(place_pos, level_number);
			block->vanish(true);
			m_Levels.emplace_back(block);
			make_entity(block, EASY_LEVELS | HARD_LEVELS | EXPERT_LEVELS);
			place_pos.x += place_offset.x + block_size.x;
		}
		place_pos.x = place_offset.x;
		place_pos.y += place_offset.y + block_size.y;
	}

	set_main_layer(DIFFICULTY_SELECTION);
}

void LevelSelection::switch_layer(uint16_t layer)
{
	std::wstring header_text;
	switch (layer) {
	case DIFFICULTY_SELECTION:
		header_text = L"WYBIERZ POZIOM";
		break;
	case EASY_LEVELS:
		header_text = L"POZIOM £ATWY";
		break;
	case HARD_LEVELS:
		header_text = L"POZIOM TRUDNY";
		break;
	case EXPERT_LEVELS:
		header_text = L"POZIOM EKSPERT";
		break;
	}

	m_HeaderText->set_text(header_text);
	m_HeaderText->center_x();
	set_main_layer(layer);
}
