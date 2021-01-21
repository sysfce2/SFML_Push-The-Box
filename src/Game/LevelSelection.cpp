#include "State/StatesManager.h"
#include "Core/Window.h"
#include "Core/Logger.h"

#include "LevelSelection.h"
#include "GamePlay.h"
#include "LevelEditor/LevelEditorMenu.h"

const sf::Color GOLDEN_BROWN{ 105, 91, 0, 255 };
const sf::Color HEADER_COLOR{ 229, 198, 0, 255 };
const vec2f SELECT_BLOCK_SCALE{ 3.f, 3.f };
const vec2f BTN_SCALE{ 4.5f, 4.5f };
const u8 BTN_FNT_SIZE = 60;

SelectBlock::SelectBlock(const vec2f& position, u16 number)
	: ElementUI("not-completed", SELECT_BLOCK_SCALE, position), m_Number(number)
{
	m_NumberText = new TextUI(std::to_string(number), "invasion", 48);
	m_PlayButton = new ButtonUI("", SELECT_BLOCK_SCALE);
	m_PlayButton->assign_button_sprite("play-btn", "play-btn-pressed");
	m_NumberText->attach_position(this).center_y(0.015f);
	m_PlayButton->attach_position(this).center_y(0.075f);
	add_child_entity(m_NumberText);
	add_child_entity(m_PlayButton);
}

void LevelSelection::update(const float& dt)
{
	u16 active_layer = layer_id();
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
	float btn_y = .2f;
	float btn_off = .15f;
	
	m_Background = new ElementUI("header-state", { 1.5f, 1.5f });
	m_HeaderText = new TextUI(L"WYBIERZ POZIOM", "joystix", 80);
	m_EasyButton = new ButtonUI(L"£ATWE", BTN_SCALE, BTN_FNT_SIZE);
	m_HardButton = new ButtonUI(L"TRUDNE", BTN_SCALE, BTN_FNT_SIZE);
	m_ExpertButton = new ButtonUI(L"EKSPERT", BTN_SCALE, BTN_FNT_SIZE);
	m_EditorButton = new ButtonUI(L"   EDYTOR\n   POZIOMóW", BTN_SCALE, 38);
	m_BackButton = new ButtonUI(L"WRÓÆ", BTN_SCALE, BTN_FNT_SIZE);

	m_HeaderText->set_tcolor(HEADER_COLOR);
	m_HeaderText->center_x(.03f);
	m_EasyButton->center_x(btn_y);
	m_HardButton->center_x(btn_y + btn_off);
	m_ExpertButton->center_x(btn_y + btn_off * 2);
	m_EditorButton->set_position({ .72f, .85f });
	m_BackButton->center_x(.85f);
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

	u16 rows = 5; u16 cols = 6;
	for (u16 i = 0; i < rows; i++) {
		for (u16 j = 0; j < cols; j++) {
			u16 level_number = i * 6 + j + 1;
			block = new SelectBlock(place_pos, level_number);
			block->vanish(true);
			if (level_number > 6)
				block->m_PlayButton->disable();
			m_Levels.emplace_back(block);
			make_entity(block, EASY_LEVELS | HARD_LEVELS | EXPERT_LEVELS);
			place_pos.x += place_offset.x + block_size.x;
		}
		place_pos.x = place_offset.x;
		place_pos.y += place_offset.y + block_size.y;
	}

	set_main_layer(DIFFICULTY_SELECTION);
}

void LevelSelection::switch_layer(u16 layer)
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
