#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <stack>
#include "Entity.h"

using StateStack = std::stack<State*>;

class State
{
public:
	friend class Application;
	friend class StatesManager;
protected:
	Entity* make_entity(Entity* entity);
	void update_entities(const float& dt);
	void render(sf::RenderTarget& target);
	void destroy_state();
	virtual void update(const float& dt) = 0;

	State();
	virtual ~State();
private:
	bool m_DestroyState = false;
protected:
	std::vector<Entity*> m_Entities;
	vec2f m_CameraOffset = { 0.f, 0.f };
};