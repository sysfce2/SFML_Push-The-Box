#pragma once
#include <SFML/Graphics.hpp>

using vec2f = sf::Vector2f;

class Entity // TODO: add unique id
{
public:
	friend class State;
	friend class StateMainMenu;
	friend class SatePlaying;

	const vec2f get_position();
	const vec2f get_position_px();
	const vec2f get_size();
	const vec2f get_size_px();
	const vec2f get_scale();
	void set_sprite(const std::string& asset_id, int x = -1, int y = -1, int w = -1, int h = -1);
	void set_position(const vec2f& position);
	void set_scale(const vec2f& scale);

protected:
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target, vec2f camera_offset);
public:
	Entity();
	virtual ~Entity();

protected:
	bool m_VisibleSprite = false;
	sf::Sprite m_Sprite;
};