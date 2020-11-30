#pragma once
#include "Core/Application.h"

class PushTheBox : public Application
{
protected:
	bool on_init() override;
	bool on_update(const float& dt) override;
public:
	PushTheBox() : Application("Push The Box") {};
	virtual ~PushTheBox() = default;
};