#pragma once
#include "UIText.h"

const float CURSOR_SPACING = 0.005f;

struct TextBoxProps
{
	std::string font;
	uint8_t font_size;
	sf::Color text_color;
	std::string cursor_texture;
};

class Cursor : public UIElement
{
public:
	friend class UITextBox;
	void update(const float& dt) override;
private:
	float m_CursorTime = 0.f;
	bool m_IsHidden = true;
};

class UITextBox : public UIElement
{
public:
	friend class Application;
	void set_max_chars(uint16_t max_chars);
	void only_numbers(bool is_true = true);
	void clear();
	inline std::wstring get_content() const { return m_Text->get_content(); }
	UITextBox(const std::string& text_box_texture, const vec2f& scale, const TextBoxProps& props);
	virtual ~UITextBox() = default;
private:
	void update(const float& dt) override;
	void update_cursor_pos();
	
	static uint32_t m_KeyEntered;
	static bool m_WasKeyEntered;
	bool m_Focused = false;
	bool m_OnlyNumbers = false;
	uint16_t m_CharsTyped = 0u;
	uint16_t m_MaxChars = 0u;
	UIText* m_Text;
	Cursor* m_Cursor;
};