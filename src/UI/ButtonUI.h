#pragma once
#include "UI/ElementUI.h"
#include "UI/TextUI.h"
#include <SFML/Graphics.hpp>
#include <chrono>

class ButtonUI : public ElementUI
{
	virtual void update(const float& dt) override;
public:
	bool was_pressed();
	inline bool is_pressed() const { return m_Pressed; }
	void set_symbol(ElementUI* symbol);
	void disable(bool disabled = true);
	inline bool is_disabled() const { return m_Disabled; }
	void assign_button_sprite(const std::string& unpressed_sprite, const std::string& pressed_sprite);
	ButtonUI(const std::string& button_name, const vec2f& scale, uint8_t font_size = 0);
	ButtonUI(const std::wstring& button_name, const vec2f& scale, uint8_t font_size);
	virtual ~ButtonUI() = default;

	static bool m_AnyPressed;
private:
	uint8_t m_FontSize = 0;
	bool m_Disabled = false;
	bool m_Pressed = false;
	bool m_ButtonEventHandled = false;
	std::chrono::milliseconds m_PressTime;
	std::string m_ButtonSprite;
	std::string m_PressedButtonSprite;
	std::wstring m_ButtonString;
	TextUI* m_ButtonText = nullptr;
	ElementUI* m_Symbol = nullptr;
};