#include "UIButton.h"
#include "WindowHandle.h"
#include "Logger.h"

const std::string DEFAULT_FONT = "invasion";
const sf::Color DEFAULT_COLOR = sf::Color(105, 91, 0, 255);

void UIButton::update(const float& dt)
{
	if (m_Visible) {
		vec2f scale = get_scale();
		auto cursor_over_button = [&]() {
			sf::FloatRect bounds = m_Sprite->getGlobalBounds();
			sf::Vector2i mouse = sf::Mouse::getPosition(*WindowHandle::get_handle());
			return bounds.contains((float)mouse.x, (float)mouse.y);
		};

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (cursor_over_button()) {
				if (!m_Hold) {
					m_Hold = true;
					set_sprite(m_ButtonAsset + "-pressed");
					if (m_ButtonText != nullptr)
						m_ButtonText->move_px(vec2f(-scale.x, scale.y));
				}
			}
			else if (m_Hold) {
				m_Hold = false;
				set_sprite(m_ButtonAsset);
				if (m_ButtonText != nullptr)
					m_ButtonText->move_px(vec2f(scale.x, -scale.y));
			}
		}
		else {
			if (m_Hold && cursor_over_button()) {
				m_PressTime = std::chrono::duration_cast<std::chrono::milliseconds>(
					std::chrono::system_clock::now().time_since_epoch());
				m_ButtonEventHandled = false;
				LOG_INFO("Button", m_ButtonName, "pressed.");
			}

			if (m_Hold) {
				m_Hold = false;
				set_sprite(m_ButtonAsset);
				if (m_ButtonText != nullptr)
					m_ButtonText->move_px(vec2f(scale.x, -scale.y));
			}
		}
	}
}

bool UIButton::was_pressed()
{
	if (!m_ButtonEventHandled) {
		auto current_time = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch());

		float pressed_ago = (current_time - m_PressTime).count() / 1000.f;
		bool pressed = pressed_ago > 0.1f && pressed_ago < 1.f;

		if (pressed)
			m_ButtonEventHandled = true;

		return pressed;
	}
	else return false;
}

bool UIButton::is_hold() const
{
	return m_Hold;
}

UIButton::UIButton(const std::string& button_name, const vec2f& scale, uint8_t font_size)
	: UIElement(font_size > 0 ? "button" : button_name, scale),
	  m_ButtonAsset(font_size > 0 ? "button" : button_name),
	  m_ButtonName(button_name), m_PressTime(0), m_FontSize(font_size)
{
	if (font_size > 0) {
		m_ButtonText = new UIText(button_name, DEFAULT_FONT, font_size);
		m_ButtonText->attach_position(this);
		m_ButtonText->center_x();
		m_ButtonText->center_y();
		m_ButtonText->set_color(DEFAULT_COLOR);
		add_child_entity(m_ButtonText);
	}
}

UIButton::~UIButton()
{
}
