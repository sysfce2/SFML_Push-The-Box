#pragma once
#include "StatePlaying.h"
#include "Player.h"

using KB = sf::Keyboard;

void StatePlaying::update(float dt)
{	
	if (KB::isKeyPressed(KB::Escape))
		destroy_state();
}

StatePlaying::StatePlaying(StateStack* states_ptr, AssetsManager* assets_manager)
	: State(states_ptr, assets_manager)
{
	auto player = make_entity(new Player(m_AssetsManager));
}

StatePlaying::~StatePlaying()
{
}