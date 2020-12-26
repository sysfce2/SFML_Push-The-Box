#include "UI/UIButton.h"
#include "Core/Window.h"
#include "Core/Logger.h"

const std::string DEFAULT_FONT = "joystix";
const sf::Color DEFAULT_COLOR = sf::Color(105, 91, 0, 255);
bool UIButton::m_AnyPressed = false;

void UIButton::update(const float& dt)
{
	if (m_Visible && !m_Disabled) {
		auto cursor_over_button = [&]() {
			sf::FloatRect bounds = m_Sprite->getGlobalBounds();
			sf::Vector2i mouse = sf::Mouse::getPosition(*Window::get_handle());
			return bounds.contains((float)mouse.x, (float)mouse.y);
		};

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (!m_Pressed && !m_AnyPressed && cursor_over_button()) {
				set_sprite(m_PressedButtonSprite);
				m_Pressed = true;
				m_AnyPressed = true;

				if (m_ButtonText != nullptr)
					m_ButtonText->shift_px({ -get_scale().x, get_scale().y });

				if (m_Symbol != nullptr)
					m_Symbol->shift_px({ -get_scale().x, get_scale().y });
			}
		}
		else {
			if (m_Pressed && cursor_over_button()) {
				m_ButtonEventHandled = false;
				m_PressTime = std::chrono::duration_cast<std::chrono::milliseconds>(
					std::chrono::system_clock::now().time_since_epoch());
			}
			if (m_Pressed) {
				set_sprite(m_ButtonSprite);
				m_Pressed = false;
				m_AnyPressed = false;

				if (m_ButtonText != nullptr)
					m_ButtonText->shift_px({ get_scale().x, -get_scale().y });

				if (m_Symbol != nullptr)
					m_Symbol->shift_px({ get_scale().x, -get_scale().y });
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
		m_ButtonEventHandled = pressed_ago > 0.1f && pressed_ago < 1.f;
		if (m_ButtonEventHandled)
			m_AnyPressed = false;

		return m_ButtonEventHandled;
	}
	else return false;
}

void UIButton::set_symbol(UIElement* symbol)
{
	m_Symbol = symbol;
	m_Symbol->attach_position(this).center_x().center_y();
	add_child_entity(m_Symbol);
}

void UIButton::disable(bool disabled)
{
	m_Disabled = disabled;
	if (m_Pressed) {
		m_Pressed = false;
		set_sprite(m_ButtonSprite);
		if (m_ButtonText != nullptr)
			m_ButtonText->shift_px({ get_scale().x, -get_scale().y });

		if (m_Symbol != nullptr)
			m_Symbol->shift_px({ get_scale().x, -get_scale().y });
	}
	
	if (disabled)
		m_Sprite->setColor(sf::Color(170, 150, 130, 120));
	else 
		m_Sprite->setColor(sf::Color(255, 255, 255, 255));
}

void UIButton::assign_button_sprite(const std::string& unpressed_sprite, const std::string& pressed_sprite)
{
	m_ButtonSprite = unpressed_sprite;
	m_PressedButtonSprite = pressed_sprite;
	set_sprite(m_ButtonSprite);
	if (m_ButtonText != nullptr)
		m_ButtonText->center_x().center_y();
}

UIButton::UIButton(const std::string& button_string, const vec2f& scale, uint8_t font_size)
	: UIElement("btn-4x1", scale), m_ButtonSprite("btn-4x1"), m_PressedButtonSprite("btn-4x1-pressed"),
	  m_ButtonString(std::wstring(button_string.begin(), button_string.end())),
	  m_PressTime(0), m_FontSize(font_size)
{
	if (button_string.length() > 0) {
		m_ButtonText = new UIText(button_string, DEFAULT_FONT, font_size);
		m_ButtonText->attach_position(this).center_x().center_y();
		m_ButtonText->set_color(DEFAULT_COLOR);
		add_child_entity(m_ButtonText);
	}
}

UIButton::UIButton(const std::wstring& button_string, const vec2f& scale, uint8_t font_size)
	: UIElement("btn-4x1", scale), m_ButtonSprite("btn-4x1"), m_PressedButtonSprite("btn-4x1-pressed"),
	  m_ButtonString(button_string), m_PressTime(0), m_FontSize(font_size)
{
	if (button_string.length() > 0) {
		m_ButtonText = new UIText(button_string, DEFAULT_FONT, font_size);
		m_ButtonText->attach_position(this).center_x().center_y();
		m_ButtonText->set_color(DEFAULT_COLOR);
		add_child_entity(m_ButtonText);
	}
}
