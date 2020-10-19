#include "StatesManager.h"

StateStack StatesManager::m_AppStates;

void StatesManager::create_active_state(State* state)
{
	m_AppStates.push(state);
}
