#include "State/StatesManager.h"

StatesManager* StatesManager::s_Instance = nullptr;
 std::stack<State*> StatesManager::m_AppStates;

void StatesManager::create_active_state(State* state)
{
	m_AppStates.emplace(state);
}

StatesManager::StatesManager()
{
}

StatesManager::~StatesManager()
{
}
