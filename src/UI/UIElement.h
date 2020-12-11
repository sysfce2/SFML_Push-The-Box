#pragma once
#include "Entity/Entity.h"

class UIElement : public Entity
{
protected:
	void update(const float& dt) override;
public:
	UIElement();
	UIElement(const std::string& asset_id, const vec2f& scale);
	virtual ~UIElement() = default;;
};