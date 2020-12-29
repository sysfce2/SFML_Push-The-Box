#include "Entity/Entity.h"
#include "Core/Window.h"
#include "Core/AssetsManager.h"
#include "Core/Logger.h"
#include <math.h>

void Entity::render(sf::RenderTarget& target, const vec2f& camera)
{
	if (m_Visible) {
		vec2f draw_pos = get_position_px();

		if (m_UseCameraPosition)
			draw_pos -= camera * Window::size();

		Entity* entity = get_attached();
		while (entity != nullptr) {
			draw_pos += entity->get_position_px();
			entity = entity->get_attached();
		}

		if (m_Sprite != nullptr) {
			m_Sprite->setPosition(draw_pos);
			target.draw(*m_Sprite);
		}
		else {
			m_RectSprite.setPosition(draw_pos);
			target.draw(m_RectSprite);
		}
	}
}

Entity& Entity::set_sprite(const std::string& asset_id, vec2i pos, vec2i size)
{
	sf::Texture* texture = AssetsManager::get().get_texture(asset_id);

	if (texture != nullptr) {
		if (m_Sprite != nullptr)
			delete m_Sprite;

		m_Sprite = new sf::Sprite();
		m_Sprite->setTexture(*texture);

		if (size.x > 0 && size.y > 0) {
			m_Sprite->setTextureRect(sf::IntRect(pos.x, pos.y, size.x, size.y));
			m_SpriteSize = size;
		}
		else m_SpriteSize = { (float)texture->getSize().x, (float)texture->getSize().y };
		set_scale(m_Scale);
	}

	return *this;
}

Entity& Entity::set_color(const sf::Color& color)
{
	if (m_Sprite != nullptr)
		m_Sprite->setColor(color);
	m_RectSprite.setFillColor(color);
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

Entity& Entity::set_size(const vec2f& size)
{
	if (m_Sprite != nullptr)
		set_scale(size / m_SpriteSize / Window::size());
	else m_Scale = { 1.f, 1.f };

	vec2f size_px = size * Window::size();
	m_RectSprite.setSize(size_px);
	m_SizePx = size_px;
	m_Size = size;
	return *this;
}

Entity& Entity::set_size_px(const vec2f& size_px)
{
	if (m_Sprite != nullptr)
		set_scale(size_px / m_SpriteSize);
	else m_Scale = { 1.f, 1.f };

	m_RectSprite.setSize((vec2f)(size_px));
	m_SizePx = size_px;
	m_Size = size_px / Window::size();

	return *this;
}

Entity& Entity::set_scale(const vec2f& scale)
{
	vec2f draw_scale = scale * Window::res_scale();
	if (m_Sprite != nullptr) {
		m_Sprite->setScale(draw_scale);
		m_SizePx = m_SpriteSize * draw_scale;
		m_Size = m_SpriteSize * draw_scale / Window::size();
		m_Scale = scale;
	}
	else if (!m_Size.is_zero()) {
		vec2f rect_init_size = vec2f(m_RectSprite.getSize().x, m_RectSprite.getSize().y) / m_Scale;
		m_RectSprite.setScale(draw_scale);
		m_SizePx = rect_init_size * scale;
		m_Size = rect_init_size * scale / Window::size();
		m_Scale = scale;
	}
	return *this;
}

Entity& Entity::set_rotation(const float& angle)
{
	m_RotationAngle = angle;
	m_Sprite->setRotation(angle);
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

void Entity::start_movement(vec2f move_offset_px, float movement_speed_px)
{
	vec2f move_ratio = { 1.f, 1.f };
	if (move_offset_px.x != 0.f && move_offset_px.y != 0.f)
		move_ratio = {
			abs(move_offset_px.x / move_offset_px.y),
			abs(move_offset_px.y / move_offset_px.x)
		};
	else {
		if (move_offset_px.x == 0.f) move_ratio.x = 0.f;
		if (move_offset_px.y == 0.f) move_ratio.y = 0.f;
	}
	move_offset_px /= Window::res_scale();
	m_DistanceLeft = { abs(move_offset_px.x) , abs(move_offset_px.y) };
	m_VelocityPx = { movement_speed_px * move_ratio.x, movement_speed_px * move_ratio.y };
	if (move_offset_px.x < 0) m_VelocityPx.x *= -1.f;
	if (move_offset_px.y < 0) m_VelocityPx.y *= -1.f;
	m_MovingToDestination = true;
}

void Entity::update_movements(const float& dt)
{
	if (m_MovingToDestination) {
		vec2i direction;
		direction.x = m_VelocityPx.x > 0 ? 1 : -1;
		direction.y = m_VelocityPx.y > 0 ? 1 : -1;
		
		if (m_DistanceLeft.x - abs(m_VelocityPx.x * dt) < 0
			|| m_DistanceLeft.y - abs(m_VelocityPx.y * dt) < 0) {
			vec2f movement;
			movement.x = m_DistanceLeft.x * direction.x;
			movement.y = m_DistanceLeft.y * direction.y;
			m_MovingToDestination = false;
			m_VelocityPx = { 0.f, 0.f };
			shift_px(movement);
			return;
		}
		m_DistanceLeft -= { abs(m_VelocityPx.x * dt), abs(m_VelocityPx.y * dt) };
	}
	if (m_VelocityPx.x != 0.f || m_VelocityPx.y != 0.f)
		shift_px(m_VelocityPx * dt);
}

void Entity::vanish(bool freeze)
{
	m_Visible = false;
	m_Freezed = freeze;
	for (auto& child : m_ChildEntities) {
		child->m_Visible = false;
		child->m_Freezed = freeze;
	}
}

void Entity::appear(bool freeze)
{
	m_Visible = true;
	m_Freezed = freeze;
	for (auto& child : m_ChildEntities) {
		child->m_Visible = true;
		child->m_Freezed = freeze;
	}
}

void Entity::destroy()
{
	m_Active = false;
}

Entity& Entity::add_child_entity(Entity* entity)
{
	m_ChildEntities.emplace_back(entity);
	return *entity;
}

Entity::Entity()
{
	m_RectSprite = sf::RectangleShape();
	m_RectSprite.setSize(vec2f(100.f, 100.f) * Window::res_scale());
	m_RectSprite.setFillColor(sf::Color::Magenta);
}

Entity::~Entity()
{
	if (m_Sprite != nullptr)
		delete m_Sprite;
}
