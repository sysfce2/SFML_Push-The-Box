#include "Core/Application.h"
#include "Core/Logger.h"
#include "UI/TextBoxUI.h"
#include "Utils/Utils.h"

#include <fstream>
#include <iostream>
#include <string>

Application::Application(const std::string& app_name, const std::string& icon_path)
	: m_AppName(app_name), m_IconPath(icon_path)
{
	Logger::init();
	AppConfig app_config = load_app_config();
	if (app_config) {
		Window::create_window(app_config);
		m_Window = Window::get_handle();
		m_InitSuccess = true;
	}
	else {
		LOG_ERROR("Couldn't load config file");
		m_InitSuccess = false;
	}
}

void Application::run(u16 fps_limit)
{
	if (!m_IsRunning) {
		if (load_resources() && on_init()) {
			m_Window->setFramerateLimit(fps_limit);
			m_IsRunning = true;
			sf::Time frame_start, frame_end;
			sf::Clock clock;

			while (m_Window->isOpen()) {
				frame_start = clock.getElapsedTime();
				if (!on_update(m_FrameTime)) {
					m_Window->close();
					LOG_ERROR("Game runtime error:", m_RuntimeErrorMessage);
				}
				handle_sfml_events();
				update_active_state(m_FrameTime);
				render_active_state();
				frame_end = clock.getElapsedTime();
				m_FrameTime = frame_end.asSeconds() - frame_start.asSeconds();
			}
		}
		else
			LOG_ERROR("Game initialization error:", m_InitErrorMessage);
	}
	else
		LOG_ERROR("Game is already running!");
}

AppConfig Application::load_app_config()
{
	std::ifstream config("app.config");
	AppConfig app_config = { 0 };
	if (config.is_open()) {
		std::string line;
		while (getline(config, line)) {
			std::vector<std::string>args = utils::str_split(line, '=');
			if (args.size() < 2) continue;

			if (args[0] == "width")
				app_config.screen_width = stoi(args[1]);
			else if (args[0] == "height")
				app_config.screen_height = stoi(args[1]);
			else if (args[0] == "fullscreen")
				app_config.fullscreen = stoi(args[1]);
		}
		config.close();
		app_config.icon_path = m_IconPath;
		app_config.app_name = m_AppName;
	}
	return app_config;
}

bool Application::load_resources()
{
	bool success = true;
	std::ifstream resources("resources");
	if (resources.is_open()) {
		std::string line;
		while (getline(resources, line))
			if (line.size() > 0 && line[0] != '#') {
				line.erase(remove(line.begin(), line.end(), ','), line.end());
				std::vector<std::string> args = utils::str_split(line, ' ');
				if (args.size() < 2) continue;

				if (args[0] == "FONT")
					success |= AssetsManager::get().load_font(args[1], args[2]);
				else
					success |= AssetsManager::get().load_texture(args[0], args[1], stoi(args[2]));
			}
		resources.close();
	}
	else {
		m_InitErrorMessage = "Failed to load game resources list";
		return false;
	}

	if (!success) {
		m_InitErrorMessage = "Failed to load game resources";
		return false;
	}
	return true;
}

Application::~Application()
{
	auto& app_states = StatesManager::get().m_AppStates;
	while (!app_states.empty()) {
		delete app_states.top();
		app_states.pop();
	}
	AssetsManager::get().free_memory();
	delete m_Window;
}

void Application::handle_sfml_events()
{
	sf::Event event;
	while (m_Window->pollEvent(event))
		switch (event.type) {
		case sf::Event::Closed:
			m_Window->close();
			break;
		case sf::Event::TextEntered:
			TextBoxUI::m_WasKeyEntered = true;
			TextBoxUI::m_KeyEntered = event.text.unicode;
			break;
		case sf::Event::GainedFocus:
			Window::m_IsFocused = true;
			break;
		case sf::Event::LostFocus:
			Window::m_IsFocused = false;
			break;
		default:
			TextBoxUI::m_WasKeyEntered = false;
			break;
		}
}

void Application::update_active_state(const float& dt)
{
	auto& app_states = StatesManager::get().m_AppStates;
	if (!app_states.top()->m_DestroyState) {
		app_states.top()->update_entities(dt);
		app_states.top()->update(dt);
	}
	else {
		delete app_states.top();
		app_states.pop();
		StatesManager::get().m_RefreshStates.pop_back();
		m_SkipNextRender = true;
	}

	if (app_states.size() == 0)
		m_Window->close();
}

void Application::render_active_state()
{
	if (!m_SkipNextRender) {
		m_Window->clear();
		StatesManager::get().m_AppStates.top()->render_entities(*m_Window);
		m_Window->display();
	}
	else
		m_SkipNextRender = false;
}