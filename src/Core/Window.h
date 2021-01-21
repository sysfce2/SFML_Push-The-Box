#pragma once
#include "Vector2.h"
#define WIDTH_MODEL   1920.f
#define HEIGHT_MODEL  1080.f

/*******************************************
============================================
Klasa okna pozwalaj¹ca na dostêp do 
parametrów okna z kod gry.
	Parametry okna:
		- D³ugoœæ (piksele)
		- Szerokoœæ (piksele)
		- Skala rozdzielczoœci
		- Fokus okna
============================================
*******************************************/

class Window
{
public:
	friend class Application;
	static sf::Window* get_handle();
	static vec2f res_scale();
	static vec2f size();
	static u16 width();
	static u16 height();
	static float aspect_ratio();
	static bool is_focused();
private:
	static void set_handle(sf::Window* window_handle);
	static void update_res_scale();

	static sf::Window* m_Handle;
	static vec2f m_ResScale;
	static u16 m_Width;
	static u16 m_Height;
	static bool m_IsFocused;
};