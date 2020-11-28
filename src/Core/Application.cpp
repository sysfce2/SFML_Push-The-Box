#include "Core/Application.h"
#include "Core/Window.h"
#include "Core/Logger.h"
#include <algorithm>

Application::Application(const std::string& app_name) 
	: m_AppStatesPtr(&StatesManager::m_AppStates), m_AppName(app_name)
{
	// TODO: JSON window config load
	m_ScreenWidth = 1280;
	m_ScreenHeight = 720;
	uint8_t fullscreen = 0; // sf::Style::Fullscreen;

	sf::Uint32 style = sf::Style::Close | fullscreen;
	m_Window.create(sf::VideoMode(m_ScreenWidth, m_ScreenHeight), m_AppName, style);
	Window::set_handle(&m_Window);
	Logger::init();
}

void Application::run(uint16_t fps_limit)
{
	if (!m_IsRunning && on_init()) {
		sf::Clock clock;
		m_Window.setFramerateLimit(fps_limit);
		m_IsRunning = true;

		while (m_Window.isOpen()) {
			sf::Time frame_start = clock.getElapsedTime();
			if (!on_update(m_FrameTime)) {
				m_Window.close();
				LOG_ERROR("Game runtime error:", m_RuntimeErrorMessage);
			}
			handle_sfml_events();
			update_active_state(m_FrameTime);
			render_active_state();
			sf::Time frame_end = clock.getElapsedTime();
			m_FrameTime = frame_end.asSeconds() - frame_start.asSeconds();
		}
	}
	else {
		if (m_IsRunning)
			m_InitErrorMessage = "game is already running!";
		LOG_ERROR("Game initialization error:", m_InitErrorMessage);
	}
}

Application::~Application()
{
	while (!StatesManager::m_AppStates.empty()) {
		delete StatesManager::m_AppStates.top();
		StatesManager::m_AppStates.pop();
	}
	AssetsManager::free_memory();
}

void Application::handle_sfml_events()
{
	sf::Event event;
	while (m_Window.pollEvent(event))
		switch (event.type) {
		case sf::Event::Closed:
			m_Window.close();
			break;
		}
}

void Application::update_active_state(const float& dt)
{
	if (!m_AppStatesPtr->top()->m_DestroyState) {
		m_AppStatesPtr->top()->update_entities(dt);
		m_AppStatesPtr->top()->update(dt);
	}
	else {
		delete m_AppStatesPtr->top();
		m_AppStatesPtr->pop();
		m_SkipNextRender = true;
	}

	if (m_AppStatesPtr->size() == 0)
		m_Window.close();
}

void Application::render_active_state()
{
	if (!m_SkipNextRender) {
		m_Window.clear();
		m_AppStatesPtr->top()->render(m_Window);
		m_Window.display();
	}
	else
		m_SkipNextRender = false;
}