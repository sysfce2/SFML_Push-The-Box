#pragma once
#include "Vector2.h"
#define WIDTH_MODEL   1920.f
#define HEIGHT_MODEL  1080.f

class Window
{
public:
	friend class Application;
	static sf::Window* get_handle();
	static vec2f res_scale();
	static vec2f size();
	static uint16_t width();
	static uint16_t height();
	static bool is_focused();
private:
	static void set_handle(sf::Window* window_handle);
	static void update_res_scale();

	static sf::Window* m_Handle;
	static vec2f m_ResScale;
	static uint16_t m_Width;
	static uint16_t m_Height;
	static bool m_IsFocused;
};