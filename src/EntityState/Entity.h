#pragma once
#include <SFML/Graphics.hpp>

using vec2f = sf::Vector2f;
using vec2u = sf::Vector2u;

class Entity
{
public:
	friend class State;
	friend class Animation;

	vec2f get_position() const;
	vec2f get_position_px() const;
	vec2f get_size() const;
	vec2f get_size_px() const;
	vec2f get_scale() const;
	void set_sprite(sf::Sprite* sprite, bool size_changed);
	void set_sprite(const std::string& asset_id, uint32_t x = 0, uint32_t y = 0, uint32_t w = 0, uint32_t h = 0);
	void set_position(const vec2f& position);
	void set_position_px(const vec2f& position);
	void set_scale(const vec2f& scale);
	void move_px(const vec2f& offset);
	void attach_position(Entity* other);
	void detach_position();
	void destroy();

protected:
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target, const vec2f& camera_offset = { 0.f, 0.f });
	void add_child_entity(Entity* entity);

public:
	Entity(const Entity& entity) = delete;
	Entity();
	virtual ~Entity();

private:
	bool m_Active = true;
	vec2f m_Scale = { 1.f, 1.f };
	vec2f m_SpriteSize = { 0.f, 0.f };
	std::vector<Entity*> m_ChildEntities;
protected:
	bool m_Visible = true;
	vec2f m_PositionPx = { 0.f, 0.f };
	vec2f m_Position = { 0.f, 0.f };
	vec2f m_SizePx = { 0.f, 0.f };
	vec2f m_Size = { 0.f, 0.f };
	sf::Sprite* m_Sprite = nullptr;
	Entity* m_AttachedToEntity = nullptr;
};