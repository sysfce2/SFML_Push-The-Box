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
	void update_entities(float dt);
	void render(sf::RenderTarget& target);
	void destroy_state();
	virtual void update(float dt) = 0;

	State(AssetsManager* assets_manager);
	virtual ~State();
private:
	bool m_DestroyState = false;
	StateStack* m_AppStatesPtr = nullptr;
protected:
	std::vector<Entity*> m_Entities;
	AssetsManager* m_AssetsManager;
};