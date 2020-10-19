#include "Entity.h"
#include "WindowHandle.h"

void Entity::render(sf::RenderTarget& target, vec2f camera_offset)
{
	if (m_VisibleSprite) {
		const vec2f before_offset = m_Sprite.getPosition();
		vec2f draw_pos = { before_offset.x - camera_offset.x * WindowHandle::width(),
			before_offset.y - camera_offset.y * WindowHandle::height() };
		m_Sprite.setPosition(draw_pos);
		target.draw(m_Sprite);
		m_Sprite.setPosition(before_offset);
	}
}

void Entity::set_sprite(const std::string& asset_id, int x, int y, int w, int h)
{
	m_VisibleSprite = true;
	m_Sprite.setTexture(*(AssetsManager::get_texture(asset_id)));
	if (h > 0) m_Sprite.setTextureRect(sf::IntRect(x, y, w, h));
}

void Entity::set_position(const vec2f& position)
{
	vec2f draw_position = { position.x * WindowHandle::width(),
		position.y * WindowHandle::height() };
	m_Sprite.setPosition(draw_position);
}

void Entity::set_scale(const vec2f& scale)
{
	vec2f final_scale = { scale.x * WindowHandle::get_ratio().x,
		scale.y * WindowHandle::get_ratio().y };
	m_Sprite.setScale(final_scale);
}

const vec2f Entity::get_position()
{
	return vec2f(m_Sprite.getPosition().x / WindowHandle::width(),
		m_Sprite.getPosition().y / WindowHandle::height());
}

const vec2f Entity::get_position_px()
{
	return m_Sprite.getPosition();
}

const vec2f Entity::get_size()
{
	auto sprite_texture = m_Sprite.getTexture();
	vec2f sprite_size = { sprite_texture->getSize().x * m_Sprite.getScale().x,
						sprite_texture->getSize().y * m_Sprite.getScale().y};
	return vec2f(sprite_size.x / WindowHandle::width(),
		sprite_size.y / WindowHandle::height());
}

const vec2f Entity::get_size_px()
{
	auto sprite_texture = m_Sprite.getTexture();
	return vec2f(sprite_texture->getSize().x * m_Sprite.getScale().x,
			sprite_texture->getSize().y * m_Sprite.getScale().y);
}

const vec2f Entity::get_scale()
{
	return m_Sprite.getScale();
}

Entity::Entity()
{
}

Entity::~Entity()
{
}
