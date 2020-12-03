#include "Entity/Entity.h"
#include "Core/Window.h"
#include "Core/AssetsManager.h"
#include "Core/Logger.h"

void Entity::render(sf::RenderTarget& target, const vec2f& camera_offset)
{
	if (m_Visible && m_Sprite != nullptr) {
		vec2f position = get_position_px();
		vec2f camera_pos = camera_offset * Window::size();
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

Entity& Entity::set_sprite(const std::string& asset_id, vec2i pos, vec2i size)
{
	sf::Texture* texture = AssetsManager::get().get_texture(asset_id);
	if (m_Sprite != nullptr)
		delete m_Sprite;

	m_Sprite = new sf::Sprite();
	m_Sprite->setTexture(*texture);
	set_scale(m_Scale);

	if (size.x > 0 && size.y > 0) {
		m_Sprite->setTextureRect(sf::IntRect(pos.x, pos.y, size.x, size.y));
		m_SpriteSize = size;
	}
	else m_SpriteSize = { (float)texture->getSize().x, (float)texture->getSize().y };

	m_SizePx = m_SpriteSize * Window::res_scale();
	m_Size = m_SizePx / Window::size();
	return *this;
}

Entity& Entity::set_sprite(sf::Sprite* sprite, bool size_changed)
{
	m_Sprite = sprite;
	if (size_changed) {
		sf::Vector2u s_size = sprite->getTexture()->getSize();
		m_SpriteSize = { (float)s_size.x, (float)s_size.y };
		m_SizePx = m_SpriteSize * Window::res_scale();
		m_Size = m_SizePx / Window::size();
	}
	return *this;
}

Entity& Entity::set_position(const vec2f& position)
{
	m_Position = position;
	m_PositionPx = position * Window::size();
	return *this;
}

Entity& Entity::set_position_px(const vec2f& position)
{
	m_Position = position / Window::size();
	m_PositionPx = position;
	return *this;
}

Entity& Entity::set_scale(const vec2f& scale)
{
	vec2f draw_scale = scale * Window::res_scale();
	if (m_Sprite != nullptr)
		m_Sprite->setScale(draw_scale);
	m_SizePx = m_SpriteSize * draw_scale;
	m_Size = m_SpriteSize * draw_scale / Window::size();
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
	set_position_px(m_PositionPx + offset * Window::res_scale());
	return *this;
}

Entity& Entity::center_x()
{
	if (m_AttachedToEntity == nullptr)
		set_position({ .5f - get_size().x / 2.f, get_position().y });
	else {
		vec2f base_center = { m_AttachedToEntity->get_size().x / 2.f, 0.f };
		set_position({ base_center.x - get_size().x / 2.f, get_position().y });
	}
	return *this;
}

Entity& Entity::center_y()
{
	if (m_AttachedToEntity == nullptr)
		set_position({ get_position().x, .5f - get_size().y / 2.f });
	else {
		vec2f base_center = { 0.f, m_AttachedToEntity->get_size().y / 2.f };
		set_position({ get_position().x, base_center.y - get_size().y / 2.f });
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
