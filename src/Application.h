#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stack>
#include "StatePlaying.h"
#include "AssetsManager.h"

class Application
{
public:
	float m_FrameTime;
	AssetsManager m_AssetsManager;
private:
	float m_TitleUpdateTimer;
	bool m_IsRunning;
	uint16_t m_ScreenWidth;
	uint16_t m_ScreenHeight;
	std::string m_AppName;
	std::string m_InitErrorMessage;
	sf::RenderWindow m_Window;
	std::stack<State*> m_AppStates;
	
public:
	void run(uint16_t fps_limit);
	Application(uint16_t screen_width, uint16_t screen_height, std::string app_name);
	~Application();
private:
	bool init_game();
	void handle_events();
	void update_all(float dt);
	void draw_all();
	void update_window_title(float dt);
};