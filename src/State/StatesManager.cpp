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

	m_AppStates.emplace(state);
	LOG_INFO("New active state created");
}
