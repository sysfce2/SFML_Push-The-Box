#include "LevelEditorMenu.h"
#include "State/StatesManager.h"
#include "Editor.h"

#include <locale>
#include <codecvt>

const sf::Color HEADER_COLOR{ 229, 198, 0, 255 };
const sf::Color TB_TEXT_COLOR{ 229, 198, 0, 255 };
const vec2f BUTTON_SCALE{ 4.5f, 4.5f };
const TextBoxProps TB_PROPS {
	"joystix", 36, TB_TEXT_COLOR, "cursor"
};

void LevelEditorMenu::update(const float& dt)
{
	u16 active_layer = layer_id();
	if (active_layer == LE_MENU) {
		if (m_bNew->was_pressed())
			set_main_layer(LE_NEW);
		if (m_bLoad->was_pressed())
			set_main_layer(LE_LOAD);
	}
	else if (active_layer == LE_NEW) {
		if (m_bCreate->was_pressed() && create_level())
			destroy_state();
	}
	else if (active_layer == LE_LOAD) {
		if (m_LevelSelector.action_was_pressed()) {
			std::string level_path = m_LevelSelector.get_level_path();
			if (level_path.size() > 0)
				StatesManager::get().create_active_state(new Editor(true, level_path));
		}
	}

	if (m_bBack->was_pressed())
		if (active_layer != LE_MENU) {
			set_main_layer(LE_MENU);
			m_tbLevelName->clear();
		}
		else destroy_state();
}

bool LevelEditorMenu::create_level()
{
	std::wstring ln_content = m_tbLevelName->get_content();
	std::wstring w_content = m_tbLevelWidth->get_content();
	std::wstring h_content = m_tbLevelHeight->get_content();

	if (ln_content.size() == 0u) return false;
	if (w_content.size() == 0u) return false;
	if (h_content.size() == 0u) return false;

	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;
	std::string level_name = converter.to_bytes(ln_content);
	vec2u size = { (unsigned)std::stoi(w_content), (unsigned)std::stoi(h_content) };

	if (size.x < 5u || size.y < 5u) return false;

	StatesManager::get().create_active_state(new Editor(false, "levels/custom/" + level_name + ".lvl", size));
	return true;
}

LevelEditorMenu::LevelEditorMenu()
{
	// Menu layer
	m_Background = new ElementUI("header-state", { 1.5f, 1.5f });
	m_HeaderText = new TextUI(L"EDYTOR POZIOMÓW", "joystix", 80);
	m_bNew = new ButtonUI(L"NOWY", BUTTON_SCALE, 60);
	m_bLoad = new ButtonUI(L"WCZYTAJ", BUTTON_SCALE, 60);
	m_bBack = new ButtonUI(L"WRÓÆ", BUTTON_SCALE, 60);

	m_HeaderText->set_tcolor(HEADER_COLOR);
	m_HeaderText->center_x(.017f);
	m_bNew->center_x(.35f);
	m_bLoad->center_x(.5f);
	m_bBack->center_x(.85f);

	make_entity(m_Background);
	make_entity(m_HeaderText);
	make_entity(m_bNew, LE_MENU);
	make_entity(m_bLoad, LE_MENU);
	make_entity(m_bBack);

	// New level layer
	m_tbLevelName = new TextBoxUI("level-name", BUTTON_SCALE, TB_PROPS);
	m_tbLevelWidth = new TextBoxUI("level-size", BUTTON_SCALE, TB_PROPS);
	m_tbLevelHeight = new TextBoxUI("level-size", BUTTON_SCALE, TB_PROPS);
	m_NewCaption1 = new TextUI(L"NAZWA POZIOMU", "joystix", 36);
	m_NewCaption2 = new TextUI(L"SZEROKOŒÆ POZIOMU (5-99)", "joystix", 36);
	m_NewCaption3 = new TextUI(L"WYSOKOŒÆ POZIOMU (5-99)", "joystix", 36);
	m_bCreate = new ButtonUI(L"STWÓRZ", BUTTON_SCALE, 60);

	m_tbLevelName->set_max_chars(16);
	m_tbLevelWidth->only_numbers(); m_tbLevelHeight->only_numbers();
	m_tbLevelWidth->set_max_chars(2); m_tbLevelHeight->set_max_chars(2);
	m_NewCaption1->center_x(.2f);
	m_tbLevelName->center_x(.25f);
	m_NewCaption2->center_x(.35f);
	m_tbLevelWidth->center_x(.4f);
	m_NewCaption3->center_x(.5f);
	m_tbLevelHeight->center_x(.55f);
	m_bCreate->center_x(.65f);

	make_entity(m_tbLevelName, LE_NEW);
	make_entity(m_tbLevelWidth, LE_NEW);
	make_entity(m_tbLevelHeight, LE_NEW);
	make_entity(m_NewCaption1, LE_NEW);
	make_entity(m_NewCaption2, LE_NEW);
	make_entity(m_NewCaption3, LE_NEW);
	make_entity(m_bCreate, LE_NEW);

	m_LevelSelector.create(this, L"WCZYTAJ", LE_LOAD);

	hide_all_layers();
	set_main_layer(LE_MENU);
}