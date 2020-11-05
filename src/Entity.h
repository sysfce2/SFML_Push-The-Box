#pragma once
#include <SFML/Graphics.hpp>

using vec2f = sf::Vector2f;
using vec2u = sf::Vector2u;

class Entity
{
public:
	friend class State;
	friend class StateMainMenu;
	friend class SatePlaying;

	vec2f get_position() const;
	vec2f get_position_px() const;
	vec2f get_size() const;
	vec2f get_size_px() const;
	vec2f get_scale() const;
	void set_sprite(const std::string& asset_id, int x = -1, int y = -1, int w = -1, int h = -1);
	void set_position(const vec2f& position);
	void set_position_px(const vec2f& position);
	void set_scale(const vec2f& scale);
	void set_origin(const vec2f& origin);
	void move_units(const vec2f& units_offset);
	void destroy();

protected:
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target, const vec2f& camera_offset);

public:
	Entity();
	virtual ~Entity();

protected:
	bool m_Visible = true;
	bool m_Active = true;
	sf::Sprite m_Sprite;
	vec2f m_PositionPx = { 0.f, 0.f };
	vec2f m_Position = { 0.f, 0.f };
	vec2f m_SizePx = { 0.f, 0.f };
	vec2f m_Size = { 0.f, 0.f };
	vec2f m_Scale = { 1.f, 1.f };
	vec2f m_SpriteSize = { 0.f, 0.f };
};