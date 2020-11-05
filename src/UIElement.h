#pragma once
#include "Entity.h"

class UIElement : public Entity
{
private:
	void update(const float& dt) override;
public:
	void center_x(UIElement* base = nullptr);
	void center_y(UIElement* base = nullptr);
	UIElement(const std::string& asset_id, const vec2f& scale);
	virtual ~UIElement();
};