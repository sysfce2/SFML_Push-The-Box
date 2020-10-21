#pragma once
#include <SFML/Graphics.hpp>

class WindowHandle
{
public:
	friend class Application;
	static void set_handle(sf::Window* window_handle);
	static void update_ratio();
	static sf::Window* get_handle();
	static sf::Vector2f get_ratio();
	static uint16_t width();
	static uint16_t height();
	static const float AspectRatioX;
private:
	static sf::Window* m_Handle;
	static sf::Vector2f m_ScreenRatio;
	static uint16_t m_Width;
	static uint16_t m_Height;
};