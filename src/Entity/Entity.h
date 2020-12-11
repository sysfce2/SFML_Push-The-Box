#pragma once
#include "Core/Vector2.h"

class Entity
{
public:
	friend class State;
	friend class Animation;

	Entity& set_sprite(sf::Sprite* sprite, bool size_changed);
	Entity& set_sprite(const std::string& asset_id, vec2i pos = { 0, 0 }, vec2i size = { 0,0 });
	Entity& set_position(const vec2f& position);
	Entity& set_position_px(const vec2f& position);
	Entity& set_scale(const vec2f& scale);
	Entity& shift(const vec2f& offset);
	Entity& shift_px(const vec2f& offset);
	Entity& center_x();
	Entity& center_y();
	Entity& attach_position(Entity* other);
	Entity& detach_position();
	inline vec2f get_position()    const { return m_Position; }
	inline vec2f get_position_px() const { return m_PositionPx; }
	inline vec2f get_size()        const { return m_Size; }
	inline vec2f get_size_px()     const { return m_SizePx; }
	inline vec2f get_scale()       const { return m_Scale; }
	void vanish(bool freeze = false);
	void appear(bool freeze = false);
	void destroy();

protected:
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target, const vec2f& camera_offset = { 0.f, 0.f });
	Entity& add_child_entity(Entity* entity);

public:
	Entity(const Entity& entity) = delete;
	Entity() = default;
	virtual ~Entity();

private:
	bool m_Active = true;
	vec2f m_Scale = { 1.f, 1.f };
	vec2f m_SpriteSize = { 0.f, 0.f };
	std::vector<Entity*> m_ChildEntities;
protected:
	bool m_Visible = true;
	bool m_Freezed = false;
	vec2f m_PositionPx = { 0.f, 0.f };
	vec2f m_Position = { 0.f, 0.f };
	vec2f m_SizePx = { 0.f, 0.f };
	vec2f m_Size = { 0.f, 0.f };
	sf::Sprite* m_Sprite = nullptr;
	Entity* m_AttachedToEntity = nullptr;
};