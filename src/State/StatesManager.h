#pragma once
#include <stack>
#include "State/State.h"

class StatesManager
{
public:
	friend class Application;
	friend class State;
	friend class Window;

	void create_active_state(State* state);

	inline static StatesManager& get() {
		if (s_Instance == nullptr)
			s_Instance = new StatesManager();
		return *s_Instance;
	}

private:
	static StatesManager* s_Instance;
	std::stack<State*> m_AppStates;
	std::vector<bool> m_RefreshStates;
};