#include "UI/UIElement.h"

void UIElement::update(const float& dt)
{
}

void UIElement::center_x()
{
	if (m_AttachedToEntity == nullptr)
		set_position(vec2f(.5f - get_size().x / 2.f, get_position().y));
	else {
		vec2f base_center = { m_AttachedToEntity->get_size().x / 2.f, 0.f };
		set_position(vec2f(base_center.x - get_size().x / 2.f, get_position().y));
	}
}

void UIElement::center_y()
{
	if (m_AttachedToEntity == nullptr) 
		set_position(vec2f(get_position().x, .5f - get_size().y / 2.f));
	else {
		vec2f base_center = { 0.f, m_AttachedToEntity->get_size().y / 2.f };
		set_position(vec2f(get_position().x, base_center.y - get_size().y / 2.f));
	}
}

UIElement::UIElement(const std::string& asset_id, const vec2f& scale)
{
	if (asset_id.size() > 0) {
		set_sprite(asset_id);
		set_scale(scale);
	}
}

UIElement::~UIElement()
{
}
