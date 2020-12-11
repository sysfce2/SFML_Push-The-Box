#include "UI/UIElement.h"

void UIElement::update(const float& dt)
{
}

UIElement::UIElement()
{
	m_Visible = false;
	m_Freezed = true;
}

UIElement::UIElement(const std::string& asset_id, const vec2f& scale)
{
	if (asset_id.size() > 0) {
		set_sprite(asset_id);
		set_scale(scale);
	}
}
