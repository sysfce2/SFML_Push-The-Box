#include "MainMenu.h"
#include "State/StatesManager.h"
#include "LevelSelection.h"

const u8 BTN_FNT_SIZE = 60;
const vec2f BTN_SCALE{ 4.5f, 4.5f };

MainMenu::MainMenu()
{
	m_Background = new ElementUI("menu-state", { 1.5f, 1.5f });
	m_Title = new ElementUI("title", { 5.25f, 5.25f });
	m_PlayButton = new ButtonUI("GRAJ", BTN_SCALE, BTN_FNT_SIZE);
	m_OptionsButton = new ButtonUI("OPCJE", BTN_SCALE, BTN_FNT_SIZE);
	m_ExitButton = new ButtonUI(L"WYJD", BTN_SCALE, BTN_FNT_SIZE);
	m_Footer = new TextUI(L"PROJEKT Z C++ WYKONA£ DAMIAN ¯UK", "joystix", 32);

	m_Title->center_x(.1f);
	m_PlayButton->center_x(.4f);
	m_OptionsButton->center_x(.55f);
	m_ExitButton->center_x(.7f);
	m_Footer->center_x(.945f);

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

	if (m_OptionsButton->was_pressed())
		system("notepad.exe app.config");

	if (m_ExitButton->was_pressed())
		destroy_state();
}

MainMenu::~MainMenu()
{
}