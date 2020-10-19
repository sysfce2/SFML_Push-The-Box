#pragma once
#include <SFML/Graphics.hpp>
#include "StatePlaying.h"
#include "StatesManager.h"
#include "StateMainMenu.h"
#include "AssetsManager.h"

class Application
{
private:
	bool init_game();
	void handle_events();
	void update_all(const float& dt);
	void draw_all();
	void update_window_title(const float& dt);
public:
	void run(uint16_t fps_limit);
	Application(uint16_t screen_width, uint16_t screen_height, const std::string& app_name);
	~Application();

private:
	StateStack* m_AppStatesPtr;
	uint16_t m_ScreenWidth;
	uint16_t m_ScreenHeight;
	std::string m_AppName;
	std::string m_InitErrorMessage;
	sf::RenderWindow m_Window;

	bool m_SkipNextRender = false;
	float m_FrameTime = 0.f;
	float m_TitleUpdateTimer = 0.f;
};