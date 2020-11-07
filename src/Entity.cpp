#include "Entity.h"
#include "WindowHandle.h"
#include "AssetsManager.h"
#include "Logger.h"

// 1000 units = 1 screen width
vec2f unitsToPx(vec2f units) {
	return { units.x * 0.001f * WindowHandle::width(), units.y * 0.001f * WindowHandle::width() };
}

void Entity::render(sf::RenderTarget& target, const vec2f& camera_offset)
{
	if (m_Visible && m_Sprite != nullptr) {
		vec2f attach_pos = { 0.f, 0.f };
		if (m_AttachedEntity != nullptr)
			attach_pos = m_AttachedEntity->get_position_px();
		vec2f draw_pos = { attach_pos.x + m_PositionPx.x - camera_offset.x * WindowHandle::width(),
			attach_pos.y + m_PositionPx.y - camera_offset.y * WindowHandle::height() };
		m_Sprite->setPosition(draw_pos);
		target.draw(*m_Sprite);
	}
}

void Entity::add_child_entity(Entity* entity)
{
	m_ChildEntities.emplace_back(entity);
}

void Entity::set_sprite(const std::string& asset_id, int x, int y, int w, int h)
{
	sf::Texture* texture = AssetsManager::get_texture(asset_id);
	if (m_Sprite != nullptr)
		delete m_Sprite;

	m_Sprite = new sf::Sprite();
	m_Sprite->setTexture(*texture);
	m_Sprite->setScale(m_Scale);

	if (h > 0) {
		m_Sprite->setTextureRect(sf::IntRect(x, y, w, h));
		m_SpriteSize = { (float)w, (float)h };
	}
	else m_SpriteSize = { (float)texture->getSize().x, (float)texture->getSize().y };

	m_SizePx = { m_SpriteSize.x * WindowHandle::get_ratio().x, m_SpriteSize.y * WindowHandle::get_ratio().y };
	m_Size = { m_SizePx.x / WindowHandle::width(), m_SizePx.y / WindowHandle::height() };
}

void Entity::set_position(const vec2f& position)
{
	vec2f draw_position = { position.x * WindowHandle::width(), position.y * WindowHandle::height() };
	m_Position = position;
	m_PositionPx = draw_position;
}

void Entity::set_scale(const vec2f& scale)
{
	vec2f draw_scale = { scale.x * WindowHandle::get_ratio().x, scale.y * WindowHandle::get_ratio().y };
	if (m_Sprite != nullptr)
		m_Sprite->setScale(draw_scale);
	m_SizePx = { m_SpriteSize.x * draw_scale.x, m_SpriteSize.y * draw_scale.y };
	m_Size = { m_SpriteSize.x / WindowHandle::width() * draw_scale.x, m_SpriteSize.y / WindowHandle::height() * draw_scale.y };
	m_Scale = scale;
}

void Entity::set_origin(const vec2f& origin) // TODO: delete?
{
	if (m_Sprite != nullptr)
		m_Sprite->setOrigin(vec2f(m_SizePx.x * origin.x, m_SizePx.y * origin.y));
}

void Entity::move_units(const vec2f& units_offset) // TODO: reimpelement
{
	vec2f in_px = unitsToPx(units_offset);
	set_position_px(vec2f(m_PositionPx.x + in_px.x, m_PositionPx.y + in_px.y));
}

void Entity::attach_position(Entity* other)
{
	m_AttachedEntity = other;
}

void Entity::detach_position()
{
	m_AttachedEntity = nullptr;
}

void Entity::destroy()
{
	m_Active = false;
}

void Entity::set_position_px(const vec2f& position)
{
	m_Position = { position.x / WindowHandle::width(), position.y / WindowHandle::height() };
	m_PositionPx = position;
}

vec2f Entity::get_position() const
{
	return m_Position;
}

vec2f Entity::get_position_px() const
{
	return m_PositionPx;
}

vec2f Entity::get_size() const
{
	return m_Size;
}

vec2f Entity::get_size_px() const
{
	return m_SizePx;
}

vec2f Entity::get_scale() const
{
	return m_Scale;
}

Entity::Entity()
{
}

Entity::~Entity()
{
	delete m_Sprite;
}
