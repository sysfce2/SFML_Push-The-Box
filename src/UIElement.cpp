#include "UIElement.h"

void UIElement::update(const float& dt)
{
}

void UIElement::center_x(UIElement* base)
{
	if (base == nullptr) {
		vec2f t_size = get_size();
		set_position(vec2f(.5f - t_size.x / 2.f, get_position().y));
	}
	else {
		vec2f base_center = base->get_position();
		base_center.x += base->get_size().x / 2.f;
		vec2f t_size = get_size();
		set_position(vec2f(base_center.x - t_size.x / 2.f, get_position().y));
	}
}

void UIElement::center_y(UIElement* base)
{
	if (base == nullptr) {
		vec2f t_size = get_size();
		set_position(vec2f(get_position().x, .5f - t_size.y / 2.f ));
	}
	else {
		vec2f base_center = base->get_position();
		base_center.y += base->get_size().y / 2.f;
		vec2f t_size = get_size();
		set_position(vec2f(get_position().x, base_center.y - t_size.y / 2.f));
	}
}

UIElement::UIElement(const std::string& asset_id, const vec2f& scale)
{
	set_sprite(asset_id);
	set_scale(scale);
}

UIElement::~UIElement()
{
}
