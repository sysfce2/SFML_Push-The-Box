#include "EntityState/Entity.h"
#include "Core/Window.h"
#include "Core/AssetsManager.h"
#include "Core/Logger.h"

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

Entity& Entity::add_child_entity(Entity* entity)
{
	m_ChildEntities.emplace_back(entity);
	return *entity;
}

Entity& Entity::set_sprite(const std::string& asset_id, uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
	sf::Texture* texture = AssetsManager::get().get_texture(asset_id);
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
	return *this;
}

Entity& Entity::set_sprite(sf::Sprite* sprite, bool size_changed)
{
	m_Sprite = sprite;
	if (size_changed) {
		m_SpriteSize = { (float)sprite->getTexture()->getSize().x, (float)sprite->getTexture()->getSize().y };
		m_SizePx = { m_SpriteSize.x * Window::res_scale().x, m_SpriteSize.y * Window::res_scale().y };
		m_Size = { m_SizePx.x / Window::width(), m_SizePx.y / Window::height() };
	}
	return *this;
}

Entity& Entity::set_position(const vec2f& position)
{
	vec2f draw_position = { position.x * Window::width(), position.y * Window::height() };
	m_Position = position;
	m_PositionPx = draw_position;
	return *this;
}

Entity& Entity::set_position_px(const vec2f& position)
{
	m_Position = { position.x / Window::width(), position.y / Window::height() };
	m_PositionPx = position;
	return *this;
}

Entity& Entity::set_scale(const vec2f& scale)
{
	vec2f draw_scale = { scale.x * Window::res_scale().x, scale.y * Window::res_scale().y };
	if (m_Sprite != nullptr)
		m_Sprite->setScale(draw_scale);
	m_SizePx = { m_SpriteSize.x * draw_scale.x, m_SpriteSize.y * draw_scale.y };
	m_Size = { m_SpriteSize.x / Window::width() * draw_scale.x, m_SpriteSize.y / Window::height() * draw_scale.y };
	m_Scale = scale;
	return *this;
}

Entity& Entity::shift(const vec2f& offset)
{
	set_position(m_Position + offset);
	return *this;
}

Entity& Entity::shift_px(const vec2f& offset)
{
	vec2f offset_scaled = { offset.x * Window::res_scale().x, offset.y * Window::res_scale().y };
	set_position_px(m_PositionPx + offset_scaled);
	return *this;
}

Entity& Entity::center_x()
{
	if (m_AttachedToEntity == nullptr)
		set_position(vec2f(.5f - get_size().x / 2.f, get_position().y));
	else {
		vec2f base_center = { m_AttachedToEntity->get_size().x / 2.f, 0.f };
		set_position(vec2f(base_center.x - get_size().x / 2.f, get_position().y));
	}
	return *this;
}

Entity& Entity::center_y()
{
	if (m_AttachedToEntity == nullptr)
		set_position(vec2f(get_position().x, .5f - get_size().y / 2.f));
	else {
		vec2f base_center = { 0.f, m_AttachedToEntity->get_size().y / 2.f };
		set_position(vec2f(get_position().x, base_center.y - get_size().y / 2.f));
	}
	return *this;
}

Entity& Entity::attach_position(Entity* other)
{
	m_AttachedToEntity = other;
	return *this;
}

Entity& Entity::detach_position()
{
	m_AttachedToEntity = nullptr;
	return *this;
}

Entity::~Entity()
{
	if (m_Sprite != nullptr)
		delete m_Sprite;
}
