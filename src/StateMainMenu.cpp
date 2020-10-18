#include "StateMainMenu.h"
#include "StatesManager.h"
#include "StatePlaying.h"

StateMainMenu::StateMainMenu(AssetsManager* assets_manager)
	: State(assets_manager)
{
	m_PlayButton = new UIButton(assets_manager, "play-button", vec2f(3.f, 3.f));
	m_PlayButton->set_position(vec2f(450.f, 250.f));
	make_entity(m_PlayButton);
}

void StateMainMenu::update(float dt)
{
	if (m_PlayButton->pressed_within(0.2f))
		StatesManager::create_active_state(new StatePlaying(m_AssetsManager));
}

StateMainMenu::~StateMainMenu()
{

}