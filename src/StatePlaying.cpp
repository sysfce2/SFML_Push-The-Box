#pragma once
#include "StatePlaying.h"
#include "Player.h"

void StatePlaying::update(float dt)
{	
}

StatePlaying::StatePlaying(AssetsManager* assets_manager)
	: State(assets_manager)
{
	auto player = make_entity(new Player(m_AssetsManager));
}

StatePlaying::~StatePlaying()
{
}