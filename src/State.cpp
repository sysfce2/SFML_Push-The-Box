#include "State.h"
#pragma once

State::State(StateStack* states_ptr, AssetsManager* assets_manager)
	: m_AssetsManager(assets_manager), m_AppStatesPtr(states_ptr),
	m_DestroyState(false)
{
}

State::~State()
{
	for (auto& ent : m_Entities)
		delete ent;
	m_Entities.clear();
}

Entity* State::make_entity(Entity* entity)
{
	m_Entities.push_back(entity);
	return entity;
}

void State::update_entities(float dt)
{
	for (auto& ent : m_Entities)
		ent->update(dt);
}

void State::render(sf::RenderTarget& target)
{
	for (auto& ent : m_Entities)
		ent->render(target);
}

void State::destroy_state()
{
	m_DestroyState = true;
}
