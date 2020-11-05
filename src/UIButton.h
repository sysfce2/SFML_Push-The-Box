#pragma once
#include <SFML/Graphics.hpp>
#include <chrono>
#include "UIElement.h"

class UIButton : public UIElement
{
public:
	bool was_pressed();
	bool is_hold() const;
	UIButton(const std::string& asset_id, const vec2f& scale);
	virtual ~UIButton();

private:
	void update(const float& dt) override;

	bool m_Hold = false;
	bool m_ButtonEventHandled = false;
	std::chrono::milliseconds m_PressTime;
	std::string m_ButtonAsset;
};