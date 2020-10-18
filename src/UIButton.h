#pragma once
#include <SFML/Graphics.hpp>
#include <chrono>
#include "Entity.h"

class UIButton : public Entity
{
public:
	bool pressed_within(float within_time);
	UIButton(AssetsManager* assets_manager, const std::string& asset_id, vec2f scale);
	virtual ~UIButton();

private:
	void update(float dt);

	bool m_Hold = false;
	bool m_HoldSpriteActive = false;
	std::chrono::milliseconds m_PressTime;
	std::string m_ButtonAsset;
};