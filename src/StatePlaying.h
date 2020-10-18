#pragma once
#include "State.h"

class StatePlaying : public State
{
private:
	void update(float dt);
public:
	StatePlaying(StateStack* states_ptr, AssetsManager* assets_manager);
	virtual ~StatePlaying();
};