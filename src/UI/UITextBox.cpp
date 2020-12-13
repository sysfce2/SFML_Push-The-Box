#include "UITextBox.h"
#include "Core/Window.h"

uint32_t UITextBox::m_KeyEntered = 0;
bool UITextBox::m_WasKeyEntered = false;

void UITextBox::set_max_chars(uint16_t max_chars)
{
	m_MaxChars = max_chars;
}

void UITextBox::only_numbers(bool is_true)
{
	m_OnlyNumbers = is_true;
}

UITextBox::UITextBox(const std::string& text_box_texture, const vec2f& scale, const TextBoxProps& props)
{
	set_sprite(text_box_texture);
	set_scale(scale);
	m_Text = new UIText("", props.font, props.font_size);
	m_Text->attach_position(this).set_position({ 0.01f, 0.f }).center_y();
	m_Cursor = new Cursor();
	m_Cursor->set_sprite(props.cursor_texture).attach_position(this)
		.set_scale(scale).center_y().vanish(true);
	update_cursor_pos();
	add_child_entity(m_Text);
	add_child_entity(m_Cursor);
}

void UITextBox::update(const float& dt)
{
	if (m_Visible) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::FloatRect bounds = m_Sprite->getGlobalBounds();
			sf::Vector2i mouse = sf::Mouse::getPosition(*Window::get_handle());

			if (bounds.contains((float)mouse.x, (float)mouse.y)) {
				m_Focused = true;
				m_Cursor->appear();
				m_Cursor->m_IsHidden = false;
			}
			else {
				m_Focused = false;
				m_Cursor->vanish(true);
				m_Cursor->m_IsHidden = true;
			}
		}

		if (m_Focused && m_WasKeyEntered) {
			m_WasKeyEntered = false;
			uint32_t key = m_KeyEntered;

			if (key == 13 || key == 27) {
				m_Focused = false;
				m_Cursor->vanish(true);
				m_Cursor->m_IsHidden = true;
				return;
			}

			if (key == 8) {
				std::wstring content = m_Text->get_content();
				if (content.length() > 0) {
					content = content.substr(0, content.size() - 1);
					m_Text->set_text(content);
					m_Text->center_y();
					m_CharsTyped--;
					update_cursor_pos();
				}
				return;
			}

			if (m_CharsTyped <= m_MaxChars || m_MaxChars == 0) {
				bool is_digit = key >= 48 && key <= 57;
				if (m_OnlyNumbers && !is_digit) return;
				if ((key >= 65 && key <= 90) || (key >= 97 && key <= 122)
					|| key == 95 || key == 45 || is_digit) {
					wchar_t entered_char = key;
					m_Text->set_text(m_Text->get_content() + entered_char);
					m_Text->center_y();
					m_CharsTyped++;
					update_cursor_pos();
				}
			}
		}
	}
}

void UITextBox::update_cursor_pos()
{
	float x_position = m_Text->get_position().x + m_Text->get_size().x + CURSOR_SPACING;
	m_Cursor->set_position({ x_position, m_Cursor->get_position().y });
}

void Cursor::update(const float& dt)
{
	if (m_IsHidden && m_Visible)
		vanish(true);

	m_CursorTime += dt;
	if (m_CursorTime >= 0.5f) {
		if (is_visible()) vanish();
		else appear();
		m_CursorTime = 0.f;
	}
}
