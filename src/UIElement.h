#pragma once
#include "Entity.h"

class UIElement : public Entity
{
protected:
	void update(const float& dt) override;
public:
	void center_x();
	void center_y();
	UIElement(const std::string& asset_id, const vec2f& scale);
	virtual ~UIElement();
};