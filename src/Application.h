#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stack>
#include "StatePlaying.h"
#include "AssetsManager.h"

class Application
{
private:
	bool init_game();
	void handle_events();
	void update_all(float dt);
	void draw_all();
	void update_window_title(float dt);
public:
	void run(uint16_t fps_limit);
	Application(uint16_t screen_width, uint16_t screen_height, std::string app_name);
	~Application();

public:
	AssetsManager m_AssetsManager;
	StateStack m_AppStates;
private:
	bool m_SkipNextRender;
	float m_FrameTime;
	float m_TitleUpdateTimer;
	uint16_t m_ScreenWidth;
	uint16_t m_ScreenHeight;
	std::string m_AppName;
	std::string m_InitErrorMessage;
	sf::RenderWindow m_Window;
};