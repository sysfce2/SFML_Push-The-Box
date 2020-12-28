#include "UI/UIElement.h"
#include "Core/Window.h"

void UIElement::update(const float& dt)
{
}

UIElement::UIElement()
{
	m_UseCameraPosition = false;
}

UIElement::UIElement(const std::string& asset_id, const vec2f& scale, const vec2f& pos)
{
	m_UseCameraPosition = false;
	if (asset_id.size() > 0) {
		set_sprite(asset_id);
		set_scale(scale);
		set_position(pos);
	}
}
