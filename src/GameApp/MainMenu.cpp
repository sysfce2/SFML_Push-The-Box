#include "MainMenu.h"
#include "EntityState/StatesManager.h"
#include "LevelSelection.h"

const uint8_t btn_font_size = 48;

MainMenu::MainMenu()
{
	m_Background = new UIElement("menu-state", vec2f(1.f, 1.f));
	make_entity(m_Background);

	m_Title = new UIElement("title", vec2f(3.5f, 3.5f));
	m_Title->set_position(vec2f(0.f, 0.1f));
	m_Title->center_x();
	make_entity(m_Title);

	m_PlayButton = new UIButton("GRAJ", vec2f(3.f, 3.f), btn_font_size);
	m_PlayButton->set_position(vec2f(0.f, .4f));
	m_PlayButton->center_x();
	make_entity(m_PlayButton);

	m_OptionsButton = new UIButton("OPCJE", vec2f(3.f, 3.f), btn_font_size);
	m_OptionsButton->set_position(vec2f(0.f, .55f));
	m_OptionsButton->center_x();
	make_entity(m_OptionsButton);

	m_ExitButton = new UIButton(L"WYJD", vec2f(3.f, 3.f), btn_font_size);
	m_ExitButton->set_position(vec2f(0.f, .70f));
	m_ExitButton->center_x();
	make_entity(m_ExitButton);

	UIText* footer = new UIText(L"PROJEKT Z C++ WYKONA£ DAMIAN ¯UK", "joystix", 20);
	footer->set_position(vec2f(.42f, .945f));
	footer->center_x();
	make_entity(footer);
}

void MainMenu::update(const float& dt)
{
	if (m_PlayButton->was_pressed())
		StatesManager::create_active_state(new LevelSelection());

	if (m_ExitButton->was_pressed())
		destroy_state();
}

MainMenu::~MainMenu()
{
}