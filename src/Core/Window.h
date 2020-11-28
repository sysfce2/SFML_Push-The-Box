#pragma once
#include <SFML/Graphics.hpp>
#define WIDTH_MODEL   1280.f
#define HEIGHT_MODEL  720.f

class Window
{
public:
	friend class Application;
	static sf::Window* get_handle();
	static sf::Vector2f res_scale();
	static uint16_t width();
	static uint16_t height();
	static const float AspectRatio;
private:
	static void set_handle(sf::Window* window_handle);
	static void update_res_scale();
	static sf::Window* m_Handle;
	static sf::Vector2f m_ResScale;
	static uint16_t m_Width;
	static uint16_t m_Height;
};