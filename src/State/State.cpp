#include "State/State.h"
#include "Core/Logger.h"
#include "UI/UIButton.h"

State::State()
{
	LOG_INFO("New active state created");
}

State::~State()
{
	for (auto& entity : m_Entities)
		delete entity;
	m_Entities.clear();
	for (auto& layer : m_Layers)
		delete layer.second;
	m_Layers.clear();
	LOG_WARN("A state was destroyed");
}

Entity* State::make_entity(Entity* entity, uint16_t layers)
{
	if (layers != 0x0)
		for (uint16_t i = 0; i < MAX_LAYERS; i++) {
			if ((layers & (1 << i)) >> i) {
				uint16_t layer_id = 1 << i;
				if (m_Layers.find(layer_id) == m_Layers.end())
					m_Layers[layer_id] = new Layer();
				Layer* layer = m_Layers[layer_id];
				auto& entities = layer->m_LayerEntities;
				if (!std::count(entities.begin(), entities.end(), entity))
					layer->m_LayerEntities.emplace_back(entity);
			}
		}

	if (!std::count(m_Entities.begin(), m_Entities.end(), entity)) {
		m_Entities.emplace_back(entity);
		for (auto& child : entity->m_ChildEntities)
			m_Entities.emplace_back(child);
	}

	return entity;
}

Layer* State::layer(uint16_t layer_id)
{
	if (m_Layers.find(layer_id) == m_Layers.end())
		m_Layers[layer_id] = new Layer();
	return m_Layers.at(layer_id);
}

void State::set_main_layer(uint16_t new_layer_id)
{	
	Layer* new_layer = layer(new_layer_id);
	new_layer->show();
	if (m_MainLayer != nullptr)
		m_MainLayer->hide();
	m_MainLayer = new_layer;
	m_MainLayerId = new_layer_id;
}

void State::update_entities(const float& dt)
{
	auto it = m_Entities.begin();
	while (it != m_Entities.end())
		if ((*it)->m_Active) {
			if (!(*it)->m_Freezed)
				(*it)->update(dt);
			it++;
		}
		else m_Entities.erase(it);
}

void State::render_entities(sf::RenderTarget& target)
{
	for (auto& ent : m_Entities)
		ent->render(target, m_Camera);
}

void State::destroy_state()
{
	m_DestroyState = true;
	UIButton::m_AnyPressed = false;
}

