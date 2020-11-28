#pragma once
#include <SFML/Graphics.hpp>
#include "EntityState/StatesManager.h"
#include "Core/AssetsManager.h"

class Application
{
public:
	void run(uint16_t fps_limit);
private:
	void handle_sfml_events();
	void update_active_state(const float& dt);
	void render_active_state();
protected:
	virtual bool on_init() = 0;
	virtual bool on_update(const float& dt) = 0;
public:
	Application(const std::string& app_name);
	~Application();

protected:
	std::string m_InitErrorMessage;
	std::string m_RuntimeErrorMessage;
private:
	StateStack* m_AppStatesPtr;
	uint16_t m_ScreenWidth;
	uint16_t m_ScreenHeight;
	std::string m_AppName;
	sf::RenderWindow m_Window;

	bool m_IsRunning = false;
	bool m_SkipNextRender = false;
	float m_FrameTime = 0.f;
};