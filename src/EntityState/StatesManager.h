#pragma once
#include <stack>
#include "EntityState/State.h"

class StatesManager
{
public:
	friend class Application;
	static void create_active_state(State* state);
private:
	static StateStack m_AppStates;
};