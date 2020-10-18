#include "WindowHandle.h"

sf::Window* WindowHandle::m_Handle;

void WindowHandle::set_handle(sf::Window* window_handle)
{
	m_Handle = window_handle;
}

sf::Window* WindowHandle::get_handle()
{
	return m_Handle;
}
