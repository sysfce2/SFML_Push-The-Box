#pragma once
#include <SFML/Graphics.hpp>
#include "State/StatesManager.h"
#include "Core/AssetsManager.h"
#include "Core/Window.h"
#include <functional>

class Application
{
public:
	friend class Window;
	void run(u16 fps_limit);
private:

	bool load_resources();
	void handle_sfml_events();
	void update_active_state(const float& dt);
	void render_active_state();
protected:
	virtual bool on_init() = 0;
	virtual bool on_update(const float& dt) = 0;
public:
	Application(const std::string& app_name, const std::string& icon_path);
	~Application();
	AppConfig load_app_config();

protected:
	std::string m_InitErrorMessage;
	std::string m_RuntimeErrorMessage;
private:
	std::string m_AppName;
	sf::RenderWindow* m_Window;
	const std::string& m_IconPath;
	bool m_RefreshEntities = false;
	bool m_IsRunning = false;
	bool m_SkipNextRender = false;
	bool m_InitSuccess = false;
	float m_FrameTime = 0.f;
};