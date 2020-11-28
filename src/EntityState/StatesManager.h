#pragma once
#include <stack>
#include "EntityState/State.h"

class StatesManager
{
public:
	friend class Application;
	friend class State;
	friend class StateMainMenu;
	friend class StateLevelSelect;
private:
	static StateStack m_AppStates;
	static void create_active_state(State* state);
};