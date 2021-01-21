#include "Core/Application.h"
#include "Core/Window.h"
#include "Core/Logger.h"
#include "UI/TextBoxUI.h"
#include <algorithm>

Application::Application(const std::string& app_name) : m_AppName(app_name)
{
	Logger::init();
	m_ScreenWidth = 1600;
	m_ScreenHeight = 900;
	u8 fullscreen = 0; // sf::Style::Fullscreen;

	sf::Uint32 style = sf::Style::Close | fullscreen;
	m_Window.create(sf::VideoMode(m_ScreenWidth, m_ScreenHeight), m_AppName, style);
	m_Window.clear();

	sf::Image icon;
	if (icon.loadFromFile("icon.bmp")) {
		m_Window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
		LOG_OK("Icon loaded");
	}

	Window::set_handle(&m_Window);
}

void Application::run(u16 fps_limit)
{
	if (!m_IsRunning && on_init()) {
		m_Window.setFramerateLimit(fps_limit);
		m_IsRunning = true;
		sf::Time frame_start, frame_end;
		sf::Clock clock;

		while (m_Window.isOpen()) {
			frame_start = clock.getElapsedTime();
			if (!on_update(m_FrameTime)) {
				m_Window.close();
				LOG_ERROR("Game runtime error:", m_RuntimeErrorMessage);
			}
			handle_sfml_events();
			update_active_state(m_FrameTime);
			render_active_state();
			frame_end = clock.getElapsedTime();
			m_FrameTime = frame_end.asSeconds() - frame_start.asSeconds();
		}
	}
	else {
		if (m_IsRunning) m_InitErrorMessage = "game is already running!";
		LOG_ERROR("Game initialization error:", m_InitErrorMessage);
	}
}

Application::~Application()
{
	auto& app_states = StatesManager::get().m_AppStates;
	while (!app_states.empty()) {
		delete app_states.top();
		app_states.pop();
	}
	AssetsManager::get().free_memory();
}

void Application::handle_sfml_events()
{
	sf::Event event;
	while (m_Window.pollEvent(event))
		switch (event.type) {
		case sf::Event::Closed:
			m_Window.close();
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
		m_SkipNextRender = true;
	}

	if (app_states.size() == 0)
		m_Window.close();
}

void Application::render_active_state()
{
	if (!m_SkipNextRender) {
		m_Window.clear();
		StatesManager::get().m_AppStates.top()->render_entities(m_Window);
		m_Window.display();
	}
	else
		m_SkipNextRender = false;
}