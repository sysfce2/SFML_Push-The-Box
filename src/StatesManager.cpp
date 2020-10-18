#include "StatesManager.h"

StateStack StatesManager::m_AppStates;

void StatesManager::create_active_state(State* state)
{
	state->m_AppStatesPtr = &StatesManager::m_AppStates;
	m_AppStates.push(state);
}
