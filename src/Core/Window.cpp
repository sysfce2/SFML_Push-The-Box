#include "Core/Window.h"

sf::Window* Window::m_Handle;
vec2f Window::m_ResScale;
u16 Window::m_Width;
u16 Window::m_Height;
bool Window::m_IsFocused = true;

void Window::set_handle(sf::Window* window_handle)
{
	m_Handle = window_handle;
	m_Width = window_handle->getSize().x;
	m_Height = window_handle->getSize().y;
	update_res_scale();
}

void Window::update_res_scale()
{
	sf::Vector2u win_size = m_Handle->getSize();
	m_ResScale = { win_size.x / WIDTH_MODEL, win_size.y / HEIGHT_MODEL };
}

sf::Window* Window::get_handle()
{
	return m_Handle;
}

vec2f Window::res_scale()
{
	return m_ResScale;
}

vec2f Window::size()
{
	return vec2f(m_Width, m_Height);
}

u16 Window::width()
{
	return m_Width;
}

u16 Window::height()
{
	return m_Height;
}

float Window::aspect_ratio()
{
	return (float)m_Width / (float)m_Height;
}

bool Window::is_focused()
{
	return m_IsFocused;
}
