#pragma once
#include "Entity.h"

class MenuTitle : public Entity
{
public:
	friend class StateMainMenu;
private:
	void update(const float& dt);
public:

	MenuTitle();
	virtual ~MenuTitle();
};