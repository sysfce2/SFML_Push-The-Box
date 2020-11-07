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
	AssetsManager::free_memory();
}

bool Application::init_game()
{
	uint8_t load_ok = 1;
	load_ok *= AssetsManager::load_texture("player-spritesheet.png", "player", true);
	load_ok *= AssetsManager::load_texture("wall.png", "wall", true);
	load_ok *= AssetsManager::load_texture("floor.png", "floor", true);
	load_ok *= AssetsManager::load_texture("target.png", "target", true);
	load_ok *= AssetsManager::load_texture("box.png", "box", true);
	load_ok *= AssetsManager::load_texture("box-gold.png", "box-gold", true);

	load_ok *= AssetsManager::load_texture("title-logo.png", "title", false);
	load_ok *= AssetsManager::load_texture("menu-state.png", "menu-state", false);
	load_ok *= AssetsManager::load_texture("play-btn.png", "play-button", false);
	load_ok *= AssetsManager::load_texture("play-btn-hold.png", "hold-play-button", false);
	load_ok *= AssetsManager::load_texture("options-btn.png", "options-button", false);
	load_ok *= AssetsManager::load_texture("options-btn-hold.png", "hold-options-button", false);
	load_ok *= AssetsManager::load_texture("exit-btn.png", "exit-button", false);
	load_ok *= AssetsManager::load_texture("exit-btn-hold.png", "hold-exit-button", false);

	load_ok *= AssetsManager::load_texture("menu-btn.png", "menu-button", false);
	load_ok *= AssetsManager::load_texture("menu-btn-hold.png", "hold-menu-button", false);
	load_ok *= AssetsManager::load_texture("back-btn.png", "back-button", false);
	load_ok *= AssetsManager::load_texture("back-btn-hold.png", "hold-back-button", false);

	load_ok *= AssetsManager::load_texture("play-level-btn.png", "play-level-button", false);
	load_ok *= AssetsManager::load_texture("play-level-btn-hold.png", "hold-play-level-button", false);
	load_ok *= AssetsManager::load_texture("select-state.png", "select-state", false);
	load_ok *= AssetsManager::load_texture("completed.png", "completed", false);
	load_ok *= AssetsManager::load_texture("not-completed.png", "not-completed", false);

	load_ok *= AssetsManager::load_font("joystix.ttf", "joystix");
	

	if (!load_ok) {
		m_InitErrorMessage = "Failed to load game resources";
		return false;
	}

	StatesManager::create_active_state(new StateMainMenu());
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

void Application::update_all(const float& dt)
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