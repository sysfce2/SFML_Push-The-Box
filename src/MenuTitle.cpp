#include "MenuTitle.h"
#include "WindowHandle.h"

void MenuTitle::update(const float& dt)
{
}

MenuTitle::MenuTitle()
{
	set_sprite("title");
	set_scale(vec2f(3.f, 3.f));
	vec2f t_size = get_size();
	set_position(vec2f(.5f - t_size.x / 2.f, .1f));
}

MenuTitle::~MenuTitle()
{
}
