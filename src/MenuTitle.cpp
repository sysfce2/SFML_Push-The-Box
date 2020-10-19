#include "MenuTitle.h"
#include "WindowHandle.h"

void MenuTitle::update(const float& dt)
{
}

void MenuTitle::center_x()
{
	vec2f t_size = get_size();
	set_position(vec2f(0.5f - t_size.x / 2.f, get_position().y));
}

MenuTitle::MenuTitle()
{
}

MenuTitle::~MenuTitle()
{
}
