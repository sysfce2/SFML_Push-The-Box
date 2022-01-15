#pragma once
#include "Vector2.h"
#define WIDTH_MODEL   1920.f
#define HEIGHT_MODEL  1080.f

struct AppConfig
{
	u16 screen_width = 0;
	u16 screen_height = 0;
	bool fullscreen;
	std::string icon_path;
	std::string app_name;

	operator bool() const {
		return screen_width > 0 && screen_height > 0;
	}
};

class Window
{
public:
	friend class Application;
	friend class State;
	friend class Entity;
	static sf::RenderWindow* get_handle();
	static vec2f res_scale();
	static vec2f size();
	static u16 width();
	static u16 height();
	static float aspect_ratio();
	static bool is_focused();
	static void create_window(AppConfig app_config);
	static inline AppConfig get_app_config() { return m_AppConfig; }

private:
	static void set_handle(sf::RenderWindow* window_handle);
	static bool load_icon(const std::string& icon_path);
	static void update_res_scale();
	static vec2f res_change_scale_offset;
	static sf::RenderWindow* m_Handle;
	static vec2f m_ResScale;
	static u16 m_Width;
	static u16 m_Height;
	static bool m_IsFocused;
	static bool* m_RefEntitiesPtr;
	static AppConfig m_AppConfig;
};