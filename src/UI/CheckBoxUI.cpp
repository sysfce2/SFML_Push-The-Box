#include "CheckBoxUI.h"
#include "Core/Window.h"

CheckBoxUI::CheckBoxUI(const std::string& sprite, const std::string& selection_glyph, vec2f scale)
	: m_SelectionGlyph(new ElementUI(selection_glyph, scale))
{
	set_sprite(sprite);
	set_scale(scale);
	m_SelectionGlyph->attach_position(this);
	add_child_entity(m_SelectionGlyph);
}

void CheckBoxUI::on_change(std::function<void(bool)> on_change_function)
{
	m_OnChangeFunction = on_change_function;
}

void CheckBoxUI::select(bool selected)
{
	m_IsSelected = selected;
	if (m_IsSelected)
		m_SelectionGlyph->appear();
	else
		m_SelectionGlyph->vanish(true);
}

void CheckBoxUI::disable(bool disabled)
{
	m_IsDisabled = disabled;
	if (disabled && m_IsSelected) select(false);
	if (disabled) set_color(sf::Color(222, 222, 222, 75));
	else  set_color(sf::Color(255, 255, 255, 255));
}

void CheckBoxUI::update(const float& dt)
{
	if (!m_IsDisabled) {
		if (!m_IsSelected && m_SelectionGlyph->is_visible())
			m_SelectionGlyph->vanish(true);

		sf::FloatRect bounds = m_Sprite->getGlobalBounds();
		sf::Vector2i mouse = sf::Mouse::getPosition(*Window::get_handle());
		bool contains = bounds.contains((float)mouse.x, (float)mouse.y);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (contains && m_Released) {
				m_Released = false;
				if (m_IsSelected && !m_CanBeUnchecked) return;
				select(!m_IsSelected);

				if (m_OnChangeFunction != nullptr)
					m_OnChangeFunction(m_IsSelected);
			}
		}
		else if (!m_Released) m_Released = true;
	}
}
