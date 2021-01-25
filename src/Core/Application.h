#pragma once
#include <SFML/Graphics.hpp>
#include "State/StatesManager.h"
#include "Core/AssetsManager.h"

/*******************************************
============================================
G³ówna klasa aplikacji odpowiedzialna za:
	- utworzenie okna
	- pêtla gry
	- wywo³anie funkcji aktualizuj¹cych
	- wywo³aniu funkcji renderuj¹cych
	- obs³u¿enie eventów SFML
============================================
*******************************************/

struct AppConfig
{
	u16 screen_width;
	u16 screen_height;
	bool fullscreen;
};

class Application
{
public:
	void run(u16 fps_limit);
private:
	bool load_app_conifg();
	bool load_resources();
	bool load_icon(const std::string& icon_path);
	void handle_sfml_events();
	void update_active_state(const float& dt);
	void render_active_state();
protected:
	virtual bool on_init() = 0;
	virtual bool on_update(const float& dt) = 0;
public:
	Application(const std::string& app_name, const std::string& icon_path);
	~Application();

protected:
	std::string m_InitErrorMessage;
	std::string m_RuntimeErrorMessage;
private:
	AppConfig m_AppConfig;
	std::string m_AppName;
	sf::RenderWindow m_Window;

	bool m_IsRunning = false;
	bool m_SkipNextRender = false;
	bool m_InitSuccess = false;
	float m_FrameTime = 0.f;
};