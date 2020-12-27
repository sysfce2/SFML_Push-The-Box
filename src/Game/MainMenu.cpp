#include "MainMenu.h"
#include "State/StatesManager.h"
#include "LevelSelection.h"

const uint8_t BTN_FNT_SIZE = 60;
const vec2f BTN_SCALE{ 4.5f, 4.5f };

MainMenu::MainMenu()
{
	m_Background = new UIElement("menu-state", { 1.5f, 1.5f });
	m_Title = new UIElement("title", { 5.25f, 5.25f });
	m_PlayButton = new UIButton("GRAJ", BTN_SCALE, BTN_FNT_SIZE);
	m_OptionsButton = new UIButton("OPCJE", BTN_SCALE, BTN_FNT_SIZE);
	m_ExitButton = new UIButton(L"WYJD", BTN_SCALE, BTN_FNT_SIZE);
	m_Footer = new UIText(L"PROJEKT Z C++ WYKONA£ DAMIAN ¯UK", "joystix", 32);

	m_Title->set_position({ 0.f, 0.1f }).center_x();
	m_PlayButton->set_position({ 0.f, .4f }).center_x();
	m_OptionsButton->set_position({ 0.f, .55f }).center_x();
	m_ExitButton->set_position({ 0.f, .70f }).center_x();
	m_Footer->set_position({ .42f, .945f }).center_x();

	make_entity(m_Background);
	make_entity(m_Title);
	make_entity(m_PlayButton);
	make_entity(m_OptionsButton);
	make_entity(m_ExitButton);
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