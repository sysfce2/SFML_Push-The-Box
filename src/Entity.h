#pragma once
#include <SFML/Graphics.hpp>
#include "AssetsManager.h"

using vec2f = sf::Vector2f;

class Entity
{
public:
	friend class State;
	friend class StateMainMenu;
	const vec2f& get_position();
	const vec2f& get_size();
protected:
	void set_sprite(std::string asset_id, int x = -1, int y = -1, int w = -1, int h = -1);
	void set_position(vec2f position);
	void set_scale(vec2f scale);
	virtual void update(float dt) = 0;
	virtual void render(sf::RenderTarget& target);
public:
	Entity(AssetsManager* assets_manager);
	virtual ~Entity();

protected:
	bool m_VisibleSprite = false;
	sf::Sprite m_Sprite;
private:
	AssetsManager* m_AssetsManager;
};