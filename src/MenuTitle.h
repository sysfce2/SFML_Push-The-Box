#pragma once
#include "Entity.h"

class MenuTitle : public Entity
{
public:
	friend class StateMainMenu;
private:
	void update(const float& dt);
public:
	void center_x();

	MenuTitle();
	virtual ~MenuTitle();
};