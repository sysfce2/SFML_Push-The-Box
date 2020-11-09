#include "Entity.h"
#include "WindowHandle.h"
#include "AssetsManager.h"
#include "Logger.h"
#include <math.h>

void Entity::render(sf::RenderTarget& target, const vec2f& camera_offset)
{
	if (m_Visible && m_Sprite != nullptr) {
		vec2f position = get_position_px();
		vec2f camera_pos = { camera_offset.x * WindowHandle::width(), camera_offset.y * WindowHandle::height() };
		vec2f draw_pos = position - camera_pos;
		if (m_AttachedEntity != nullptr)
			draw_pos += m_AttachedEntity->get_position_px();
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
	set_scale(m_Scale);

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

void Entity::move_px(const vec2f& offset)
{
	vec2f offset_scaled = { offset.x * WindowHandle::get_ratio().x, offset.y * WindowHandle::get_ratio().y };
	set_position_px(m_PositionPx + offset_scaled);
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
