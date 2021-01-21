#include "State/State.h"
#include "State/StatesManager.h"
#include "Core/Logger.h"
#include "UI/ButtonUI.h"

Entity* State::make_entity(Entity* entity, u16 layers)
{
	if (layers != 0x0)
		for (u16 i = 0; i < MAX_LAYERS; i++) {
			if ((layers & (1 << i)) >> i) {
				Layer* _layer = layer(1 << i);
				auto& entities = _layer->m_LayerEntities;
				if (!std::count(entities.begin(), entities.end(), entity))
					_layer->m_LayerEntities.emplace_back(entity);
			}
		}

	if (!std::count(m_Entities.begin(), m_Entities.end(), entity)) {
		m_Entities.emplace_back(entity);
		for (auto& child : entity->m_ChildEntities)
			make_entity(child, layers);
	}

	return entity;
}

Layer* State::layer(u16 layer_id)
{
	if (m_Layers.find(layer_id) == m_Layers.end())
		m_Layers[layer_id] = new Layer();
	return m_Layers.at(layer_id);
}

void State::set_main_layer(u16 new_layer_id)
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
	ButtonUI::m_AnyPressed = false;
}

State::~State()
{
	LOG_INFO("State id:", m_StateId , "was destroyed");

	for (auto& entity : m_Entities)
		delete entity;
	m_Entities.clear();

	for (auto& layer : m_Layers)
		delete layer.second;
	m_Layers.clear();
}
