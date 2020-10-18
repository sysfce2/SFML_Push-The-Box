#include "UIButton.h"
#include "WindowHandle.h"
#include "Logger.h"

void UIButton::update(float dt)
{
	auto cursor_over_button = [&]() {
		sf::FloatRect bounds = m_Sprite.getGlobalBounds();
		sf::Vector2i mouse_pos = sf::Mouse::getPosition(*WindowHandle::get_handle());
		return bounds.contains((float)mouse_pos.x, (float)mouse_pos.y);
	};

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (cursor_over_button()) {
			m_Hold = true;
			if (!m_HoldSpriteActive) {
				m_HoldSpriteActive = true;
				set_sprite("hold-" + m_ButtonAsset);
			}
		} else m_Hold = false;
	}
	else {
		if (m_Hold && cursor_over_button()) {
			m_PressTime = std::chrono::duration_cast<std::chrono::milliseconds>(
						  std::chrono::system_clock::now().time_since_epoch());
			LOG_INFO("Button", m_ButtonAsset, "pressed.");
		}

		if (m_HoldSpriteActive) {
			m_HoldSpriteActive = false;
			set_sprite(m_ButtonAsset);
		}
		m_Hold = false;
	}
}

bool UIButton::pressed_within(float within_time)
{
	auto current_time = std::chrono::duration_cast<std::chrono::milliseconds>(
						std::chrono::system_clock::now().time_since_epoch());

	float pressed_ago = (current_time - m_PressTime).count() / 1000.f;
	return pressed_ago > within_time && pressed_ago < within_time + 1.f;
}

UIButton::UIButton(AssetsManager* assets_manager, const std::string& asset_id, vec2f scale)
	: Entity(assets_manager), m_ButtonAsset(asset_id)
{
	set_sprite(asset_id);
	set_scale(scale);
}

UIButton::~UIButton()
{
}
