#include "Entity.h"

void Entity::render(sf::RenderTarget& target)
{
	if (m_VisibleSprite)
		target.draw(m_Sprite);
}

void Entity::set_sprite(std::string asset_id, int x, int y, int w, int h)
{
	m_VisibleSprite = true;
	m_Sprite.setTexture(*(m_AssetsManager->get_texture(asset_id)));
	if (h > 0) m_Sprite.setTextureRect(sf::IntRect(x, y, w, h));
}

void Entity::set_position(vec2f position)
{
	m_Position = position;
	if (m_VisibleSprite)
		m_Sprite.setPosition(position);
}

void Entity::set_scale(vec2f scale)
{
	m_Sprite.setScale(scale);
}

const vec2f& Entity::get_position()
{
	return m_Position;
}

const vec2f& Entity::get_size()
{
	auto sprite_texture = m_Sprite.getTexture();
	return vec2f(sprite_texture->getSize().x * m_Sprite.getScale().x,
			sprite_texture->getSize().y * m_Sprite.getScale().y);
}

Entity::Entity(AssetsManager* assets_manager)
	: m_VisibleSprite(false), m_AssetsManager(assets_manager)
{
}

Entity::~Entity()
{
}
