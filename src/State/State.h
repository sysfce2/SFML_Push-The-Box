#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <stack>
#include "Entity/Entity.h"
#include "Layer.h"

class State
{
public:
	friend class Application;
	friend class StatesManager;
protected:
	Entity* make_entity(Entity* entity, uint16_t layers = 0x0);
	Layer* layer(uint16_t layer_id);
	inline uint16_t layer_id() const { return m_MainLayerId; }
	void set_main_layer(uint16_t new_layer_id);
	void update_entities(const float& dt);
	void render_entities(sf::RenderTarget& target);
	void destroy_state();
	virtual void update(const float& dt) = 0;

	State();
	virtual ~State();
private:
	bool m_DestroyState = false;
protected:
	Layer* m_MainLayer = nullptr;
	uint16_t m_MainLayerId = 0x0;
	std::vector<Entity*> m_Entities;
	std::map<uint16_t, Layer*> m_Layers;
	vec2f m_CameraOffset = { 0.f, 0.f };
};