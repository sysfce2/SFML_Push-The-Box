#include "UI/UIButton.h"
#include "Core/Window.h"
#include "Core/Logger.h"

const std::string DEFAULT_FONT = "joystix";
const sf::Color DEFAULT_COLOR = sf::Color(105, 91, 0, 255);
bool UIButton::m_AnyPressed = false;

void UIButton::update(const float& dt)
{
	if (m_Visible) {
		auto cursor_over_button = [&]() {
			sf::FloatRect bounds = m_Sprite->getGlobalBounds();
			sf::Vector2i mouse = sf::Mouse::getPosition(*Window::get_handle());
			return bounds.contains((float)mouse.x, (float)mouse.y);
		};

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (!m_Pressed && !m_AnyPressed && cursor_over_button()) {
				set_sprite(m_ButtonAsset + "-pressed");
				m_Pressed = true;
				m_AnyPressed = true;
				if (m_ButtonText != nullptr)
					m_ButtonText->shift_px({ -get_scale().x, get_scale().y });
			}
		}
		else {
			if (m_Pressed && cursor_over_button()) {
				m_ButtonEventHandled = false;
				m_PressTime = std::chrono::duration_cast<std::chrono::milliseconds>(
					std::chrono::system_clock::now().time_since_epoch());
			}
			if (m_Pressed) {
				set_sprite(m_ButtonAsset);
				m_Pressed = false;
				m_AnyPressed = false;
				if (m_ButtonText != nullptr)
					m_ButtonText->shift_px({ get_scale().x, -get_scale().y });
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

bool UIButton::is_pressed() const
{
	return m_Pressed;
}

UIButton::UIButton(const std::string& button_name, const vec2f& scale, uint8_t font_size)
	: UIElement(font_size > 0 ? "button" : button_name, scale),
	  m_ButtonAsset(font_size > 0 ? "button" : button_name),
	  m_ButtonName(std::wstring(button_name.begin(), button_name.end())),
	  m_PressTime(0), m_FontSize(font_size)
{
	if (font_size > 0) {
		m_ButtonText = new UIText(button_name, DEFAULT_FONT, font_size);
		m_ButtonText->attach_position(this).center_x().center_y();
		m_ButtonText->set_color(DEFAULT_COLOR);
		add_child_entity(m_ButtonText);
	}
}

UIButton::UIButton(const std::wstring& button_name, const vec2f& scale, uint8_t font_size)
	: UIElement("button", scale), m_ButtonAsset("button"),
	  m_ButtonName(button_name), m_PressTime(0), m_FontSize(font_size)
{
	m_ButtonText = new UIText(button_name, DEFAULT_FONT, font_size);
	m_ButtonText->attach_position(this).center_x().center_y();
	m_ButtonText->set_color(DEFAULT_COLOR);
	add_child_entity(m_ButtonText);
}

UIButton::~UIButton()
{
}
