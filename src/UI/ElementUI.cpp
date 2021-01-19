#include "UI/ElementUI.h"
#include "Core/Window.h"

void ElementUI::update(const float& dt)
{
}

ElementUI::ElementUI()
{
	m_UseCameraPosition = false;
}

ElementUI::ElementUI(const std::string& asset_id, const vec2f& scale, const vec2f& pos)
{
	m_UseCameraPosition = false;
	if (asset_id.size() > 0) {
		set_sprite(asset_id);
		set_scale(scale);
		set_position(pos);
	}
}
