#include "UI/UIElement.h"

void UIElement::update(const float& dt)
{
}

UIElement::UIElement()
{
	m_IsUIElement = true;
	m_Visible = false;
	m_Freezed = true;
}

UIElement::UIElement(const std::string& asset_id, const vec2f& scale, const vec2f& pos)
{
	m_IsUIElement = true;
	if (asset_id.size() > 0) {
		set_sprite(asset_id);
		set_scale(scale);
		set_position(pos);
	}
}
