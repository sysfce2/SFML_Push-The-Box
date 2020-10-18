#pragma once
#include <SFML/Graphics.hpp>
#include "AssetsManager.h"

using vec2f = sf::Vector2f;

class Entity
{
public:
	friend class State;
private:
	vec2f m_Position;
	bool has_sprite;
	sf::Sprite m_Sprite;
	AssetsManager* m_AssetsManager;

	virtual void update(float dt) = 0;
	virtual void render(sf::RenderTarget& target);
public:
	void set_sprite(std::string name_id, int left = -1, int top = -1, int width = -1, int height = -1);
	void set_position(vec2f position);
	void set_scale(vec2f scale);
	const vec2f& get_position();
	Entity(AssetsManager* assets_manager);
	virtual ~Entity();
};