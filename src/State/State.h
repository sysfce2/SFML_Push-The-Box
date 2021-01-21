#pragma once
#include "Core/Vector2.h"
#include "Entity/Entity.h"
#include "Layer.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <stack>

class State
{
public:
	friend class Application;
	friend class StatesManager;

protected:

	Entity* make_entity(Entity* entity, u16 layers = 0x0);
	Layer* layer(u16 layer_id);
	inline u16 layer_id() const { return m_MainLayerId; }
	void set_main_layer(u16 new_layer_id);
	void update_entities(const float& dt);
	void render_entities(sf::RenderTarget& target);
	void destroy_state();
	virtual void update(const float& dt) = 0;

	State() = default;
	virtual ~State();

private:
	u16 m_StateId = 0;
	bool m_DestroyState = false;

protected:
	Layer* m_MainLayer = nullptr;
	u16 m_MainLayerId = 0;
	std::vector<Entity*> m_Entities;
	std::map<u16, Layer*> m_Layers;
	vec2f m_Camera = { 0.f, 0.f };
};