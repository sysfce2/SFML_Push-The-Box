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
protected:
	Entity* make_entity(Entity* entity);
	void update_entities(float dt);
	void render(sf::RenderTarget& target);
	void destroy_state();
	virtual void update(float dt) = 0;

	State(StateStack* states_ptr, AssetsManager* assets_manager);
	virtual ~State();
private:
	bool m_DestroyState;
	StateStack* m_AppStatesPtr;
	std::vector<Entity*> m_Entities;
protected:
	AssetsManager* m_AssetsManager;
};