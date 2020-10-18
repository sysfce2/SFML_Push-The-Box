#pragma once
#include <SFML/Graphics.hpp>

class WindowHandle
{
public:
	friend class Application;
	static void set_handle(sf::Window* window_handle);
	static sf::Window* get_handle();

private:
	static sf::Window* m_Handle;
};