#include "StateMainMenu.h"
#include "StatesManager.h"
#include "StatePlaying.h"

StateMainMenu::StateMainMenu()
{
	m_Title = new MenuTitle();
	m_Title->set_sprite("title");
	m_Title->set_position(vec2f(0.f, .1f));
	m_Title->set_scale(vec2f(3.f, 3.f));
	m_Title->center_x();
	make_entity(m_Title);

	m_PlayButton = new UIButton("play-button", vec2f(3.f, 3.f));
	m_PlayButton->set_position(vec2f(0.f, .4f));
	m_PlayButton->center_x();
	make_entity(m_PlayButton);

	m_OptionsButton = new UIButton("options-button", vec2f(3.f, 3.f));
	m_OptionsButton->set_position(vec2f(0.f, .55f));
	m_OptionsButton->center_x();
	make_entity(m_OptionsButton);

	m_ExitButton = new UIButton("exit-button", vec2f(3.f, 3.f));
	m_ExitButton->set_position(vec2f(0.f, .70f));
	m_ExitButton->center_x();
	make_entity(m_ExitButton);

}

void StateMainMenu::update(const float& dt)
{
	if (m_PlayButton->was_pressed())
		StatesManager::create_active_state(new StatePlaying());

	if (m_ExitButton->was_pressed())
		destroy_state();
}

StateMainMenu::~StateMainMenu()
{
}