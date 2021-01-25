#include "PushTheBox.h"
#include "MainMenu.h"
#include "Core/Logger.h"
#include "Progress.h"

bool PushTheBox::on_init()
{
	GameProgress::get().load();
	StatesManager::get().create_active_state(new MainMenu());
	return true;
}

bool PushTheBox::on_update(const float& dt)
{
	return true;
}

PushTheBox::PushTheBox()
	: Application("Push The Box", "assets/box-gold.png")
{ }
