#include "Core/Application.h"
#include "Core/Window.h"
#include "Core/Logger.h"
#include <algorithm>

Application::Application(uint16_t screen_width, uint16_t screen_height, const std::string& app_name, bool fullscreen)
	:	m_ScreenWidth(screen_width), m_ScreenHeight(screen_height), m_AppName(app_name),
		m_AppStatesPtr(&StatesManager::m_AppStates), m_FullScreen(fullscreen)
{
	sf::Uint32 style = sf::Style::Close;
	if (fullscreen)
		style |= sf::Style::Fullscreen;
	m_Window.create(sf::VideoMode(m_ScreenWidth, m_ScreenHeight), m_AppName, style);
	Window::set_handle(&m_Window);
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
	load_ok *= AssetsManager::load_texture("title-logo.png", "title", false);
	load_ok *= AssetsManager::load_texture("menu-state.png", "menu-state", false);
	load_ok *= AssetsManager::load_texture("button.png", "button", false);
	load_ok *= AssetsManager::load_texture("button-pressed.png", "button-pressed", false);

	load_ok *= AssetsManager::load_texture("play-btn.png", "play-btn", false);
	load_ok *= AssetsManager::load_texture("play-btn-pressed.png", "play-btn-pressed", false);
	load_ok *= AssetsManager::load_texture("select-state.png", "select-state", false);
	load_ok *= AssetsManager::load_texture("completed.png", "completed", false);
	load_ok *= AssetsManager::load_texture("not-completed.png", "not-completed", false);

	load_ok *= AssetsManager::load_texture("player-spritesheet.png", "player-ss", true);
	load_ok *= AssetsManager::load_texture("wall.png", "wall0", true);
	load_ok *= AssetsManager::load_texture("wall1.png", "wall1", true);
	load_ok *= AssetsManager::load_texture("target.png", "target", true);
	load_ok *= AssetsManager::load_texture("box.png", "box", true);
	load_ok *= AssetsManager::load_texture("box-gold.png", "box-gold", true);
	load_ok *= AssetsManager::load_texture("floor.png", "floor0", true);
	load_ok *= AssetsManager::load_texture("floor1.png", "floor1", true);
	load_ok *= AssetsManager::load_texture("floor2.png", "floor2", true);
	load_ok *= AssetsManager::load_texture("floor3.png", "floor3", true);
	load_ok *= AssetsManager::load_texture("floor4.png", "floor4", true);

	load_ok *= AssetsManager::load_font("joystix.ttf", "joystix");
	load_ok *= AssetsManager::load_font("INVASION2000.TTF", "invasion");
	load_ok *= AssetsManager::load_font("PressStart2P.TTF", "PS2P");

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