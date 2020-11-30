#include "MainMenu.h"
#include "State/StatesManager.h"
#include "LevelSelection.h"

const uint8_t btn_font_size = 48;

MainMenu::MainMenu()
{
	m_Background = new UIElement("menu-state", vec2f(1.f, 1.f));
	make_entity(m_Background);

	m_Title = new UIElement("title", vec2f(3.5f, 3.5f));
	m_Title->set_position(vec2f(0.f, 0.1f)).center_x();
	make_entity(m_Title);

	m_PlayButton = new UIButton("GRAJ", vec2f(3.f, 3.f), btn_font_size);
	m_PlayButton->set_position(vec2f(0.f, .4f)).center_x();
	make_entity(m_PlayButton);

	m_OptionsButton = new UIButton("OPCJE", vec2f(3.f, 3.f), btn_font_size);
	m_OptionsButton->set_position(vec2f(0.f, .55f)).center_x();
	make_entity(m_OptionsButton);

	m_ExitButton = new UIButton(L"WYJD", vec2f(3.f, 3.f), btn_font_size);
	m_ExitButton->set_position(vec2f(0.f, .70f)).center_x();
	make_entity(m_ExitButton);

	m_Footer = new UIText(L"PROJEKT Z C++ WYKONA£ DAMIAN ¯UK", "joystix", 20);
	m_Footer->set_position(vec2f(.42f, .945f)).center_x();
	make_entity(m_Footer);
}

void MainMenu::update(const float& dt)
{
	if (m_PlayButton->was_pressed())
		StatesManager::get().create_active_state(new LevelSelection());

	if (m_ExitButton->was_pressed())
		destroy_state();
}

MainMenu::~MainMenu()
{
}