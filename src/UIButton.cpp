#include "UIButton.h"
#include "WindowHandle.h"
#include "Logger.h"

void UIButton::update(const float& dt)
{
	auto cursor_over_button = [&]() {
		sf::FloatRect bounds = m_Sprite.getGlobalBounds();
		sf::Vector2i mouse = sf::Mouse::getPosition(*WindowHandle::get_handle());
		return bounds.contains((float)mouse.x, (float)mouse.y);
	};

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (cursor_over_button()) {
			if (!m_Hold) {
				m_Hold = true;
				set_sprite("hold-" + m_ButtonAsset);
			}
		}
		else if (m_Hold) {
			m_Hold = false;
			set_sprite(m_ButtonAsset);
		}
	}
	else {
		if (m_Hold && cursor_over_button()) {
			m_PressTime = std::chrono::duration_cast<std::chrono::milliseconds>(
				std::chrono::system_clock::now().time_since_epoch());
			m_ButtonEventHandled = false;
			LOG_INFO("Button", m_ButtonAsset, "pressed.");
		}

		if (m_Hold) {
			m_Hold = false;
			set_sprite(m_ButtonAsset);
		}
	}
}

bool UIButton::pressed_within(float within_time)
{
	if (!m_ButtonEventHandled) {
		
		auto current_time = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch());

		float pressed_ago = (current_time - m_PressTime).count() / 1000.f;
		bool was_pressed = pressed_ago > within_time && pressed_ago < within_time + 1.f;

		if (was_pressed)
			m_ButtonEventHandled = true;

		return was_pressed;
	}
	else return false;
}

void UIButton::center_x()
{
	vec2f b_size = get_size();
	set_position(vec2f(0.5f - b_size.x / 2.f, get_position().y));
}

UIButton::UIButton(const std::string& asset_id, const vec2f& scale)
	: m_ButtonAsset(asset_id), m_PressTime(0)
{
	set_sprite(asset_id);
	set_scale(scale);
}

UIButton::~UIButton()
{
}
