#include "State.h"
#include "Logger.h"

State::State()
{
	LOG_INFO("New active state created");
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

void State::update_entities(const float& dt)
{
	auto it = m_Entities.begin();
	while (it != m_Entities.end()) {
		if ((*it)->m_Active) {
			(*it)->update(dt);
			it++;
		}
		else {
			delete* it;
			m_Entities.erase(it);
		}	
	}	
}

void State::render(sf::RenderTarget& target)
{
	for (auto& ent : m_Entities)
		ent->render(target, m_CameraOffset);
}

void State::destroy_state()
{
	m_DestroyState = true;
}

