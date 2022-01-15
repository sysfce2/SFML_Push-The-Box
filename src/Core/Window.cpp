#include "Core/Window.h"
#include "Core/Logger.h"
#include "Core/Application.h"
#include "State/StatesManager.h"

sf::RenderWindow* Window::m_Handle;
vec2f Window::m_ResScale;
vec2f Window::res_change_scale_offset = { 1.f, 1.f };
u16 Window::m_Width;
u16 Window::m_Height;
bool Window::m_IsFocused = true;
bool* Window::m_RefEntitiesPtr = nullptr;
AppConfig Window::m_AppConfig;

void Window::set_handle(sf::RenderWindow* window_handle)
{
	m_Handle = window_handle;
}


void Window::create_window(AppConfig app_config)
{
	bool first_init = true;
	if (!m_Handle)
		m_Handle = new sf::RenderWindow;
	else 
		first_init = false;

	if (m_Handle->isOpen()) {
		m_Handle->close();
		for (auto ref : StatesManager::get().m_RefreshStates)
			ref = true;
	}

	m_Handle->create(sf::VideoMode(app_config.screen_width, app_config.screen_height), app_config.app_name,
		sf::Style::Close | (app_config.fullscreen ? sf::Style::Fullscreen : 0));

	load_icon(app_config.icon_path);
	m_Handle->clear();
	m_Handle->display();

	u16 ww = m_Handle->getSize().x;
	u16 wh = m_Handle->getSize().y;

	if (!first_init) 
		res_change_scale_offset = { (float)ww / (float)m_Width, (float)wh / (float)m_Height };

	m_Width = ww;
	m_Height = wh;
	m_AppConfig = app_config;
	update_res_scale();
}

bool Window::load_icon(const std::string& icon_path)
{
	sf::Image icon;
	if (icon.loadFromFile(icon_path)) {
		m_Handle->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
		LOG_OK("Application icon loaded");
	}
	else {
		LOG_ERROR("Failed to load application icon'");
		return false;
	}
	return true;
}

void Window::update_res_scale()
{
	sf::Vector2u win_size = m_Handle->getSize();
	m_ResScale = { win_size.x / WIDTH_MODEL, win_size.y / HEIGHT_MODEL };
}

sf::RenderWindow* Window::get_handle()
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
