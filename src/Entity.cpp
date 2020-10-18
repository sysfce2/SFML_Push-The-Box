#include "Entity.h"

void Entity::render(sf::RenderTarget& target)
{
	if (has_sprite)
		target.draw(m_Sprite);
}

void Entity::set_sprite(std::string name_id, int left, int top, int width, int height)
{
	has_sprite = true;
	m_Sprite.setTexture(*(m_AssetsManager->get_texture(name_id)));
	if (height > 0)
		m_Sprite.setTextureRect(sf::IntRect(left, top, width, height));
}

void Entity::set_position(vec2f position)
{
	m_Position = position;
	if (has_sprite)
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

Entity::Entity(AssetsManager* assets_manager)
	: has_sprite(false), m_AssetsManager(assets_manager)
{
}

Entity::~Entity()
{
}
