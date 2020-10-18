#include "Application.h"
#include "WindowHandle.h"
#include "Logger.h"
#include <algorithm>

Application::Application(uint16_t screen_width, uint16_t screen_height, const std::string& app_name)
	:	m_ScreenWidth(screen_width), m_ScreenHeight(screen_height), m_AppName(app_name),
		m_Window(sf::VideoMode(m_ScreenWidth, m_ScreenHeight), m_AppName, sf::Style::Close),
		m_AppStatesPtr(&StatesManager::m_AppStates)
{
	WindowHandle::set_handle(&m_Window);
	Logger::init();
}

void Application::run(uint16_t fps_limit)
{
	if (init_game()) {
		sf::Clock clock;
		m_Window.setFramerateLimit(fps_limit);

		while (m_Window.isOpen()) {
			sf::Time frame_start = clock.getElapsedTime();
			handle_events();
			update_all(m_FrameTime);
			draw_all();
			sf::Time frame_end = clock.getElapsedTime();
			m_FrameTime = frame_end.asSeconds() - frame_start.asSeconds();
			update_window_title(m_FrameTime);
		}
	}
	else LOG_ERROR("Game initialization error:", m_InitErrorMessage);
}

Application::~Application()
{
	while (!StatesManager::m_AppStates.empty()) {
		delete StatesManager::m_AppStates.top();
		StatesManager::m_AppStates.pop();
	}
}

bool Application::init_game()
{
	uint8_t load_ok = 1;
	load_ok *= m_AssetsManager.load_texture("player-spritesheet.png", "player", true);
	load_ok *= m_AssetsManager.load_texture("wall-sprite.png", "wall", false);
	load_ok *= m_AssetsManager.load_texture("play-btn.png", "play-button", false);
	load_ok *= m_AssetsManager.load_texture("play-btn-hold.png", "hold-play-button", false);
	load_ok *= m_AssetsManager.load_texture("title-logo.png", "title", false);

	if (!load_ok) {
		m_InitErrorMessage = "Failed to load game resources";
		return false;
	}

	StatesManager::create_active_state(new StateMainMenu(&m_AssetsManager));
	return true;
}

void Application::handle_events()
{
	sf::Event event;
	while (m_Window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			m_Window.close();
			break;
		}
	}
}

void Application::update_all(float dt)
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

void Application::draw_all()
{
	if (!m_SkipNextRender) {
		m_Window.clear();
		m_AppStatesPtr->top()->render(m_Window);
		m_Window.display();
	}
	else
		m_SkipNextRender = false;
}

void Application::update_window_title(float dt)
{
	if ((m_TitleUpdateTimer += dt) >= 0.2f) {
		m_Window.setTitle(m_AppName + " - FPS: " + std::to_string(static_cast<int>(1.f / dt)));
		m_TitleUpdateTimer = 0.f;
	}
}
