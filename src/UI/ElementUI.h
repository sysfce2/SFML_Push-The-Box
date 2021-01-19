#pragma once
#include "Entity/Entity.h"

class ElementUI : public Entity
{
protected:
	virtual void update(const float& dt) override;
public:
	ElementUI();
	ElementUI(const std::string& asset_id, const vec2f& scale, const vec2f& pos = { 0.f, 0.f });
	virtual ~ElementUI() = default;;
};