#include "WindowHandle.h"

sf::Window* WindowHandle::m_Handle;
sf::Vector2f WindowHandle::m_ScreenRatio;
uint16_t WindowHandle::m_Width;
uint16_t WindowHandle::m_Height;

void WindowHandle::set_handle(sf::Window* window_handle)
{
	m_Handle = window_handle;
	m_Width = window_handle->getSize().x;
	m_Height = window_handle->getSize().y;
	update_ratio();
}

void WindowHandle::update_ratio()
{
	auto win_size = m_Handle->getSize();
	m_ScreenRatio = sf::Vector2f(win_size.x / 1280.f, win_size.y / 720.f);
}

sf::Window* WindowHandle::get_handle()
{
	return m_Handle;
}

sf::Vector2f WindowHandle::get_ratio()
{
	return m_ScreenRatio;
}

uint16_t WindowHandle::width()
{
	return m_Width;
}

uint16_t WindowHandle::height()
{
	return m_Height;
}
