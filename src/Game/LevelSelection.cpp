#include "State/StatesManager.h"
#include "Core/Window.h"
#include "Core/Logger.h"
#include "LevelSelection.h"
#include "GamePlay.h"
#include "Progress.h"
#include "LevelEditor/LevelEditorMenu.h"

#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

const vec2f SELECT_BLOCK_SCALE{ 3.f, 3.f };
const vec2f BTN_SCALE{ 4.5f, 4.5f };
std::vector<SelectBlock*> LevelSelection::m_Levels;

void SelectBlock::refresh()
{
	LevelInfo* info = GameProgress::get().get_level_info(m_Number);
	if (info != nullptr) {
		if (info->completed) {
			set_sprite("completed");
			u32 elapsed = info->time;
			u32 epds = elapsed % 60; elapsed -= epds;
			u32 epdm = elapsed / 60;
			std::wstring wss = std::to_wstring(epds);
			std::wstring wsm = std::to_wstring(epdm);
			if (epds < 10) wss = L"0" + wss;
			if (epdm < 10) wsm = L"0" + wsm;
			m_tTime->set_text(L"Czas: " + wsm + L":" + wss);
			m_tMoves->set_text(L"Ruchy: " + std::to_wstring(info->moves));
		}
		else
			set_sprite("not-completed");
	}
}

SelectBlock::SelectBlock(vec2f position, u16 number)
	: ElementUI("not-completed", SELECT_BLOCK_SCALE, position), m_Number(number)
{
	m_tNumber = new TextUI(std::to_string(number), "joystix", 36);
	m_tTime = new TextUI("Czas: -:-", "joystix", 24);
	m_tMoves = new TextUI("Ruchy: -", "joystix", 24);
	m_bPlay = new ButtonUI("", SELECT_BLOCK_SCALE);
	m_bPlay->assign_button_sprite("play-btn", "play-btn-pressed");
	m_tNumber->set_tcolor({ 229, 198, 0, 255 });
	m_tNumber->attach_position(this).center_y(.0135f);
	m_tTime->attach_position(this).set_position({.053f, .027f});
	m_tMoves->attach_position(this).set_position({ .053f, .058f });
	m_bPlay->attach_position(this).center_y(.17f);
	if (number < 10) {
		m_tTime->shift({ -.015f, 0.f });
		m_tMoves->shift({ -.015f, 0.f });
	}
	add_child_entity(m_tNumber);
	add_child_entity(m_tTime);
	add_child_entity(m_tMoves);
	add_child_entity(m_bPlay);
	refresh();
}

void LevelSelection::update(const float& dt)
{
	for (auto& b : m_Levels) if (b->m_bPlay->was_pressed()) {
		std::string file_path = std::to_string(b->m_Number);
		if (b->m_Number > 9) file_path = "level" + file_path + ".lvl";
		else file_path = "level0" + file_path + ".lvl";
		file_path = "levels/" + file_path;
		StatesManager::get().create_active_state(new GamePlay(file_path, b->m_Number));
	}

	if (m_bCustom->was_pressed())
		StatesManager::get().create_active_state(new CustomLevels());

	if (m_bEditor->was_pressed())
		StatesManager::get().create_active_state(new LevelEditorMenu());

	if (m_bBack->was_pressed())
		destroy_state();
}

LevelSelection::LevelSelection()
{
	m_Background = new ElementUI("header-state", { 1.5f, 1.5f });
	m_HeaderText = new TextUI(L"WYBIERZ POZIOM", "joystix", 80);
	m_bEditor = new ButtonUI(L"   EDYTOR\n   POZIOMóW", BTN_SCALE, 38);
	m_bCustom = new ButtonUI(L"STWORZONE\n POZIOMY", BTN_SCALE, 38);
	m_bBack = new ButtonUI(L"WRÓÆ", BTN_SCALE, 60);

	m_HeaderText->set_tcolor({229, 198, 0, 255});
	m_HeaderText->center_x(.03f);
	m_bBack->center_x(.85f);

	float x = m_bBack->get_position().x, length = m_bBack->get_size().x;
	m_bCustom->set_position({ x - length - .08f, .85f });
	m_bEditor->set_position({ x + length + .08f, .85f });
	m_bEditor->assign_button_sprite("editor-btn", "editor-btn-pressed");
	
	make_entity(m_Background);
	make_entity(m_HeaderText);
	make_entity(m_bBack);
	make_entity(m_bCustom);
	make_entity(m_bEditor);

	u16 rows = 4, cols = 4;
	SelectBlock* block = new SelectBlock({ 0.f, 0.f }, 1);
	vec2f block_size =	block->get_size();
	vec2f place_offset = { (1.f - block_size.x * float(rows)) / float(rows + 1), .06f };
	vec2f place_pos = { place_offset.x, .18f };
	delete block;
	
	for (u16 i = 0; i < rows; i++) {
		for (u16 j = 0; j < cols; j++) {
			u16 level_number = i * rows + j + 1;
			block = new SelectBlock(place_pos, level_number);
			m_Levels.emplace_back(block);
			make_entity(block);
			place_pos.x += place_offset.x + block_size.x;
		}
		place_pos.x = place_offset.x;
		place_pos.y += place_offset.y + block_size.y;
	}
}

LevelSelection::~LevelSelection()
{
	m_Levels.clear();
}

CustomLevels::CustomLevels()
{
	m_Background = new ElementUI("header-state", { 1.5f, 1.5f });
	m_HeaderText = new TextUI(L"WYBIERZ POZIOM", "joystix", 80);
	m_bBack = new ButtonUI(L"WRÓÆ", BTN_SCALE, 60);
	m_HeaderText->set_tcolor({ 229, 198, 0, 255 });
	m_HeaderText->center_x(.03f);
	m_bBack->center_x(.85f);

	make_entity(m_Background);
	make_entity(m_HeaderText);
	make_entity(m_bBack);
	m_LevelSelector.create(this, L"GRAJ");
}

void CustomLevels::update(const float& dt)
{
	if (m_LevelSelector.action_was_pressed()) {
		std::string path = m_LevelSelector.get_level_path();
		std::wstring name = m_LevelSelector.get_level_name();
		if (path.size() > 0 && name.size() > 0)
			StatesManager::get().create_active_state(new GamePlay(path, -1, name));
	}

	if (m_bBack->was_pressed())
		destroy_state();
}

void CustomLevelSelector::create(State* owner_state, std::wstring action_btn_name, u16 add_to_layers)
{
	m_LevelList = new SelectListUI({ .3f, .05f }, 10);
	m_bScrollUp = new ButtonUI("", { 3.f, 3.f }, 36);
	m_bScrollDown = new ButtonUI("", { 3.f, 3.f }, 36);
	m_bSelectAction = new ButtonUI(action_btn_name, { 4.f, 4.f }, 48);
	
	auto get_file_name = [&](std::string path) -> std::string {
		std::string name;
		bool dot = false;
		for (int i = path.length() - 1; i >= 0; i--) {
			if (dot) {
				if (path[i] == '/')
					break;
				name = path[i] + name;
			}
			else if (path[i] == '.')
				dot = true;
		}
		return name;
	};

	std::string path = "levels/custom/";
	for (const auto& entry : fs::directory_iterator(path)) {
		std::string fp = entry.path().u8string();
		std::string ext = fp.substr(fp.size() - 4, 4);
		if (ext == ".lvl") {
			std::string file = get_file_name(fp);
			m_LevelList->add_element(std::wstring(file.begin(), file.end()), fp);
		}
	}

	ElementUI* arrow_up = new ElementUI("arrow_up", { 3.f, 3.f });
	ElementUI* arrow_down = new ElementUI("arrow_down", { 3.f, 3.f });
	m_bScrollUp->assign_button_sprite("btn-1x1", "btn-1x1-pressed");
	m_bScrollDown->assign_button_sprite("btn-1x1", "btn-1x1-pressed");
	m_bScrollUp->set_symbol(arrow_up);
	m_bScrollDown->set_symbol(arrow_down);
	m_LevelList->center_x(.15f);

	vec2f list_pos = m_LevelList->get_position();
	vec2f list_size = m_LevelList->get_size();

	float off = .02f;
	float x_pos = list_pos.x + list_size.x + off;
	m_bScrollUp->set_position({ x_pos, list_pos.y + off });
	m_bScrollDown->set_position({ x_pos, list_pos.y + list_size.y - m_bScrollDown->get_size().y - off });
	m_bSelectAction->set_position({x_pos + off, list_pos.y + list_size.y / 2.f - m_bSelectAction->get_size().y / 2.f});

	m_LevelList->set_scroll_up_button(m_bScrollUp);
	m_LevelList->set_scroll_down_button(m_bScrollDown);
	
	owner_state->make_entity(m_LevelList, add_to_layers);
	owner_state->make_entity(m_bScrollUp, add_to_layers);
	owner_state->make_entity(m_bScrollDown, add_to_layers);
	owner_state->make_entity(m_bSelectAction, add_to_layers);
}

bool CustomLevelSelector::action_was_pressed()
{
	return m_bSelectAction->was_pressed();
}

std::string CustomLevelSelector::get_level_path()
{
	return m_LevelList->get_selected_value();
}

std::wstring CustomLevelSelector::get_level_name()
{
	return m_LevelList->get_selected_name();
}
