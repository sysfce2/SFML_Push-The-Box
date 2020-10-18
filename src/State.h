#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Entity.h"

class State
{
public:
	friend class Application;
	Entity* make_entity(Entity* entity);
	AssetsManager* m_AssetsManager;
	State(AssetsManager* assets_manager);
	virtual ~State();
private:
	std::vector<Entity*> entities;
	virtual void update(float dt) = 0;
	void update_entities(float dt);
	void render(sf::RenderTarget& target);
};