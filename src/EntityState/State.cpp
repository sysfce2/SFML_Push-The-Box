#include "EntityState/State.h"
#include "Core/Logger.h"

State::State()
{
	LOG_INFO("New active state created");
}

State::~State()
{
	m_Entities.clear();
}

Entity* State::make_entity(Entity* entity)
{
	m_Entities.emplace_back(entity);
	for (auto& child : entity->m_ChildEntities)
		m_Entities.emplace_back(child);
	return entity;
}

void State::update_entities(const float& dt)
{
	auto it = m_Entities.begin();
	while (it != m_Entities.end())
		if ((*it)->m_Active) {
			(*it)->update(dt);
			it++;
		}
		else m_Entities.erase(it);
}

void State::render_entities(sf::RenderTarget& target)
{
	for (auto& ent : m_Entities)
		ent->render(target, m_CameraOffset);
}

void State::destroy_state()
{
	m_DestroyState = true;
}

