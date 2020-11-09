#pragma once
#include <SFML/Graphics.hpp>
#include <chrono>
#include "UIElement.h"
#include "UIText.h"

class UIButton : public UIElement
{
public:
	bool was_pressed();
	bool is_hold() const;
	UIButton(const std::string& button_name, const vec2f& scale, uint8_t font_size = 0);
	virtual ~UIButton();

private:
	void update(const float& dt) override;

	uint8_t m_FontSize = 0;
	bool m_Hold = false;
	bool m_ButtonEventHandled = false;
	std::chrono::milliseconds m_PressTime;
	std::string m_ButtonAsset;
	std::string m_ButtonName;
	UIText* m_ButtonText = nullptr;
};