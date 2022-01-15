#include "SelectListUI.h"
#include "Core/Window.h"

const sf::Color BACKGROUND_COLOR = { 28,28,76,255 };
const sf::Color SELECTED_COLOR = { 96,96,242,255 };
const sf::Color NOSELECTED_COLOR = { 56,56,160,255 };

ListElement* SelectListUI::add_element(const std::wstring& display_name, const std::string& value)
{
	m_AllElements.emplace_back(ListElementInfo{ display_name, value });
	ListElement* element = nullptr;
	if (m_ElementsTotal < m_DisplayElementsCount) {
		element = m_ListElements.at(m_ElementsTotal);
		element->set_disp_name(display_name);
		element->set_value(value);
		element->m_Number = m_ElementsTotal;
		if (m_ElementsTotal == 0) {
			element->select();
		}
	}
	else if (m_ElementsTotal == m_DisplayElementsCount)
		m_ListElements.at(m_ElementsTotal - 1)->make_three_dots();
	m_ElementsTotal++;
	return element;
}

void SelectListUI::set_scroll_up_button(ButtonUI* button)
{
	m_ScrollUpButton = button;
}

void SelectListUI::set_scroll_down_button(ButtonUI* button)
{
	m_ScrollDownButton = button;
}

std::string SelectListUI::get_selected_value()
{
	if (m_CurrentSelected == nullptr)
		return std::string();
	return m_CurrentSelected->get_value();
}

std::wstring SelectListUI::get_selected_name()
{
	if (m_CurrentSelected == nullptr)
		return std::wstring();
	return m_CurrentSelected->get_name();
}

SelectListUI::SelectListUI(vec2f element_size, u16 elements_count, PositionPressFn on_position_press)
	: m_ElementSize(element_size), m_DisplayElementsCount(elements_count), m_OnPositionPress(on_position_press)
{
	set_color(BACKGROUND_COLOR);
	set_size({ element_size.x + m_BackgroundPadding * 2.f / Window::aspect_ratio(), 
		(element_size.y + m_ElementOffset) * elements_count + m_BackgroundPadding });

	vec2f next_pos = { m_BackgroundPadding / Window::aspect_ratio(), m_BackgroundPadding};
	for (u16 i = 0; i < elements_count; i++) {
		ListElement* element = new ListElement(m_ElementSize, this);
		element->attach_position(this).set_position(next_pos);
		next_pos.y += element->get_size().y + m_ElementOffset;
		m_ListElements.emplace_back(element);
		add_child_entity(element);
	}
}

void SelectListUI::refresh_list()
{
	for (u16 i = m_ScrollOffset; i < m_ScrollOffset + m_DisplayElementsCount; i++) {
		ListElement* element = m_ListElements.at(i - m_ScrollOffset);

		if (i == m_ScrollOffset && m_ScrollOffset > 0) {
			if (element == m_CurrentSelected) {
				ListElement* next = m_ListElements.at(i - m_ScrollOffset + 1);
				next->select();
				m_CurrentSelected = next;
			}
			element->make_three_dots();
			continue;
		}

		if (i == m_ScrollOffset + m_DisplayElementsCount - 1) {
			if (i < m_AllElements.size() - 1) {
				if (element == m_CurrentSelected) {
					ListElement* previous = m_ListElements.at(i - m_ScrollOffset - 1);
					previous->select();
				}
				element->make_three_dots();
				break;
			}
		}

		if (i < m_AllElements.size()) {
			element->set_disp_name(m_AllElements.at(i).m_DisplayName);
			element->set_value(m_AllElements.at(i).m_Value);
		}
		else {
			element->set_disp_name(L"");
			element->set_value("");
		}
	}
}

void SelectListUI::update(const float& dt)
{
	if (m_ScrollUpButton != nullptr && m_ScrollUpButton->was_pressed())
		if (m_ScrollOffset > 0) {
			m_ScrollOffset--;
			refresh_list();
		}

	if (m_ScrollDownButton != nullptr && m_ScrollDownButton->was_pressed())
		if (m_ScrollOffset + m_DisplayElementsCount < (u16)m_AllElements.size()) {
			m_ScrollOffset++;
			refresh_list();
		}
}

ListElement::ListElement(vec2f element_size, SelectListUI* list_ptr)
	: ElementUI(), m_ListPtr(list_ptr)
{
	set_size(element_size);
	set_color(NOSELECTED_COLOR);
	m_tDisplay = new TextUI(L"", "joystix", 24);
	m_tDisplay->attach_position(this).center_y(.025f);
	add_child_entity(m_tDisplay);
}

void ListElement::update(const float& dt)
{
	if (Window::is_focused() && m_Visible) {

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::FloatRect bounds = m_RectSprite.getGlobalBounds();
			sf::Vector2i mouse = sf::Mouse::getPosition(*Window::get_handle());
			
			if (bounds.contains((float)mouse.x, (float)mouse.y)) {
				ListElement* current = m_ListPtr->m_CurrentSelected;
				if (current != this && m_Value.length() > 0) {
					select();
					if (m_ListPtr->m_OnPositionPress) {
						m_ListPtr->m_OnPositionPress(this);
					}
				}
			}
		}
	}
}

void ListElement::select()
{
	if (m_ListPtr->m_CurrentSelected != nullptr)
		m_ListPtr->m_CurrentSelected->set_color(NOSELECTED_COLOR);
	m_ListPtr->m_CurrentSelected = this;
	m_ListPtr->m_SelectedNumber = m_Number;
	set_color(SELECTED_COLOR);
}

void ListElement::make_three_dots()
{
	m_tDisplay->set_text(L"...");
	m_tDisplay->center_x().center_y();
	m_Value = "";
}

void ListElement::set_disp_name(const std::wstring& disp_name)
{
	m_DisplayName = disp_name;
	m_tDisplay->set_text(disp_name);
	m_tDisplay->center_y(.025f);
}

void ListElement::set_value(const std::string& value)
{
	m_Value = value;
}
