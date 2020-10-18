#pragma once
#include <stack>
#include "State.h"

class StatesManager
{
public:
	friend class Application;
	friend class State;
	friend class StateMainMenu;
private:
	static StateStack m_AppStates;
	static void create_active_state(State* state);
};