#include "LevelEditorMenu.h"

const sf::Color HEADER_COLOR{ 229, 198, 0, 255 };
const sf::Color TB_TEXT_COLOR{ 229, 198, 0, 255 };
const vec2f BUTTON_SCALE{ 3.f, 3.f };
const TextBoxProps TB_PROPS {
	"joystix", 18, TB_TEXT_COLOR, "cursor"
};

void LevelEditorMenu::update(const float& dt)
{
	uint16_t active_layer = layer_id();
	if (active_layer == LE_MENU) {
		if (m_NewButton->was_pressed())
			set_main_layer(LE_NEW);
		if (m_LoadButton->was_pressed())
			set_main_layer(LE_LOAD);
	}

	if (m_BackButton->was_pressed())
		if (active_layer != LE_MENU) 
			set_main_layer(LE_MENU);
		else destroy_state();
}

LevelEditorMenu::LevelEditorMenu()
{
	m_Background = new UIElement("select-state", { 1.f, 1.f });
	m_HeaderText = new UIText(L"EDYTOR POZIOMÓW", "joystix", 54);
	m_NewButton = new UIButton(L"NOWY", BUTTON_SCALE, 42);
	m_LoadButton = new UIButton(L"WCZYTAJ", BUTTON_SCALE, 42);
	m_BackButton = new UIButton(L"WRÓÆ", BUTTON_SCALE, 42);
	m_LevelName = new UITextBox("level-name", BUTTON_SCALE, TB_PROPS);

	m_HeaderText->set_position({ 0.f, .017f }).center_x();
	m_NewButton->set_position({ 0.f, .35f }).center_x();
	m_LoadButton->set_position({ 0.f, .5f }).center_x();
	m_BackButton->set_position({ 0.f, 0.85f }).center_x();
	m_LevelName->set_position({ 0.f, .35f }).center_x();

	m_LevelName->set_max_chars(16);
	m_HeaderText->set_color(HEADER_COLOR);

	make_entity(m_Background);
	make_entity(m_HeaderText);
	make_entity(m_NewButton, LE_MENU);
	make_entity(m_LoadButton, LE_MENU);
	make_entity(m_BackButton);
	make_entity(m_LevelName, LE_NEW);

	set_main_layer(LE_MENU);
}