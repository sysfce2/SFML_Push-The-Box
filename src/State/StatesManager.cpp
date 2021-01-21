#include "State/StatesManager.h"
#include "Core/Logger.h"

StatesManager* StatesManager::s_Instance = nullptr;
 std::stack<State*> StatesManager::m_AppStates;

void StatesManager::create_active_state(State* state)
{
	if (m_AppStates.size() > 0 && m_AppStates.top()->m_DestroyState) {
		delete m_AppStates.top();
		m_AppStates.pop();
	}

	state->m_StateId = (u16)m_AppStates.size();
	m_AppStates.emplace(state);
	LOG_INFO("Created State id:", state->m_StateId);
}
