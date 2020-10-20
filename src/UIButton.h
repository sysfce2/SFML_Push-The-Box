#pragma once
#include <SFML/Graphics.hpp>
#include <chrono>
#include "Entity.h"

class UIButton : public Entity
{
public:
	bool was_pressed();
	void center_x();
	UIButton(const std::string& asset_id, const vec2f& scale);
	virtual ~UIButton();

private:
	void update(const float& dt);

	bool m_Hold = false;
	bool m_ButtonEventHandled = false;
	std::chrono::milliseconds m_PressTime;
	std::string m_ButtonAsset;
};