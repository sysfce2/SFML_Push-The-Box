#include "EntityState/Entity.h"
#include "Core/Window.h"
#include "Core/AssetsManager.h"
#include "Core/Logger.h"
#include <math.h>

void Entity::render(sf::RenderTarget& target, const vec2f& camera_offset)
{
	if (m_Visible && m_Sprite != nullptr) {
		vec2f position = get_position_px();
		vec2f camera_pos = { camera_offset.x * Window::width(), camera_offset.y * Window::height() };
		vec2f draw_pos = position - camera_pos;
		if (m_AttachedToEntity != nullptr)
			draw_pos += m_AttachedToEntity->get_position_px();
		m_Sprite->setPosition(draw_pos);
		target.draw(*m_Sprite);
	}
}

void Entity::add_child_entity(Entity* entity)
{
	m_ChildEntities.emplace_back(entity);
}

void Entity::set_sprite(const std::string& asset_id, uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
	sf::Texture* texture = AssetsManager::get_texture(asset_id);
	if (m_Sprite != nullptr)
		delete m_Sprite;

	m_Sprite = new sf::Sprite();
	m_Sprite->setTexture(*texture);
	set_scale(m_Scale);

	if (w > 0 && h > 0) {
		m_Sprite->setTextureRect(sf::IntRect(x, y, w, h));
		m_SpriteSize = { (float)w, (float)h };
	}
	else m_SpriteSize = { (float)texture->getSize().x, (float)texture->getSize().y };

	m_SizePx = { m_SpriteSize.x * Window::res_scale().x, m_SpriteSize.y * Window::res_scale().y };
	m_Size = { m_SizePx.x / Window::width(), m_SizePx.y / Window::height() };
}

void Entity::set_sprite(sf::Sprite* sprite, bool size_changed)
{
	m_Sprite = sprite;
	if (size_changed) {
		m_SpriteSize = { (float)sprite->getTexture()->getSize().x, (float)sprite->getTexture()->getSize().y };
		m_SizePx = { m_SpriteSize.x * Window::res_scale().x, m_SpriteSize.y * Window::res_scale().y };
		m_Size = { m_SizePx.x / Window::width(), m_SizePx.y / Window::height() };
	}
}

void Entity::set_position(const vec2f& position)
{
	vec2f draw_position = { position.x * Window::width(), position.y * Window::height() };
	m_Position = position;
	m_PositionPx = draw_position;
}

void Entity::set_position_px(const vec2f& position)
{
	m_Position = { position.x / Window::width(), position.y / Window::height() };
	m_PositionPx = position;
}

void Entity::set_scale(const vec2f& scale)
{
	vec2f draw_scale = { scale.x * Window::res_scale().x, scale.y * Window::res_scale().y };
	if (m_Sprite != nullptr)
		m_Sprite->setScale(draw_scale);
	m_SizePx = { m_SpriteSize.x * draw_scale.x, m_SpriteSize.y * draw_scale.y };
	m_Size = { m_SpriteSize.x / Window::width() * draw_scale.x, m_SpriteSize.y / Window::height() * draw_scale.y };
	m_Scale = scale;
}

void Entity::move_px(const vec2f& offset)
{
	vec2f offset_scaled = { offset.x * Window::res_scale().x, offset.y * Window::res_scale().y };
	set_position_px(m_PositionPx + offset_scaled);
}

void Entity::attach_position(Entity* other)
{
	m_AttachedToEntity = other;
}

void Entity::detach_position()
{
	m_AttachedToEntity = nullptr;
}

void Entity::destroy()
{
	m_Active = false;
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
	if (m_Sprite != nullptr)
		delete m_Sprite;
}