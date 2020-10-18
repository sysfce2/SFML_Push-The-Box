#include "State.h"
#pragma once

State::State(AssetsManager* assets_manager)
	: m_AssetsManager(assets_manager)
{
}

State::~State()
{
	for (auto& ent : entities)
		delete ent;
	entities.clear();
}

Entity* State::make_entity(Entity* entity)
{
	entities.push_back(entity);
	return entity;
}

void State::update_entities(float dt)
{
	for (auto& ent : entities)
		ent->update(dt);
}

void State::render(sf::RenderTarget& target)
{
	for (auto& ent : entities)
		ent->render(target);
}
