#include "Core/Window.h"

sf::Window* Window::m_Handle;
sf::Vector2f Window::m_ResScale;
uint16_t Window::m_Width;
uint16_t Window::m_Height;

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
	m_ResScale = sf::Vector2f(win_size.x / WIDTH_MODEL, win_size.y / HEIGHT_MODEL);
}

sf::Window* Window::get_handle()
{
	return m_Handle;
}

sf::Vector2f Window::res_scale()
{
	return m_ResScale;
}

uint16_t Window::width()
{
	return m_Width;
}

uint16_t Window::height()
{
	return m_Height;
}
