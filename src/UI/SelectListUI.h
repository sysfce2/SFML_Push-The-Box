#pragma once
#include "TextUI.h"
#include "ButtonUI.h"

#include <vector>
#include <functional>

struct ListElementInfo
{
	std::wstring m_DisplayName;
	std::string m_Value;
};
class ListElement;

using PositionPressFn = std::function<void(ListElement*)>;

class SelectListUI : public ElementUI
{
public:
	friend class ListElement;
	ListElement* add_element(const std::wstring& display_name, const std::string& value);
	void set_scroll_up_button(ButtonUI* button);
	void set_scroll_down_button(ButtonUI* button);
	std::string get_selected_value();
	std::wstring get_selected_name();
	
	SelectListUI(vec2f element_size, u16 elements_count, PositionPressFn on_position_press = [](ListElement*) {});

private:
	void refresh_list();
	virtual void update(const float& dt) override;
	const float m_ElementOffset = .01f;
	const float m_BackgroundPadding = .01f;
	PositionPressFn m_OnPositionPress = nullptr;
	std::vector<ListElement*> m_ListElements;
	std::vector<ListElementInfo> m_AllElements;
	ListElement* m_CurrentSelected = nullptr;
	ButtonUI* m_ScrollUpButton = nullptr;
	ButtonUI* m_ScrollDownButton = nullptr;
	u16 m_DisplayElementsCount;
	u16 m_ScrollOffset = 0;
	u16 m_SelectedNumber = 0;
	u16 m_ElementsTotal = 0;
	vec2f m_ElementSize;
};

class ListElement : public ElementUI
{
public:
	friend class SelectListUI;
	std::string get_value() const { return m_Value; };
	std::wstring get_name() const { return m_DisplayName; };
	void select();

	ListElement(vec2f element_size, SelectListUI* list_ptr);

private:
	void update(const float& dt) override;
	void make_three_dots();
	void set_disp_name(const std::wstring& disp_name);
	void set_value(const std::string& value);

	SelectListUI* m_ListPtr;
	TextUI* m_tDisplay;
	u16 m_Number = 0;
	std::string m_Value;
	std::wstring m_DisplayName;
};