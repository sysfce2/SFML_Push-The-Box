#include "Options.h"
#include "Core/Logger.h"
#include "Utils/Utils.h"
#include <fstream>

const vec2f BTN_SCALE{ 4.5f, 4.5f };
const int supported_resolutions[][2] = { 
	{1920, 1080},
	{1600, 900},
	{1366, 768},
	{1280, 720},
	{1152, 648}
};

void Options::update(const float& dt)
{
	if (m_bApply->was_pressed()) {
		Window::create_window(m_AppConfig);
		std::ofstream cfg("app.config");
		std::string content = "width=" + std::to_string(m_AppConfig.screen_width);
		content += "\nheight=" + std::to_string(m_AppConfig.screen_height);
		content += "\nfullscreen=" + std::to_string(m_AppConfig.fullscreen);
		cfg << content;
		cfg.close();
	}

	if (m_bBack->was_pressed())
		destroy_state();
}

Options::Options()
{
	m_Background = new ElementUI("header-state", { 1.5f, 1.5f });
	m_HeaderText = new TextUI(L"OPCJE", "joystix", 80);
	m_ResText = new TextUI(L"ROZDZIELCZOŒÆ", "joystix", 32);
	m_bApply = new ButtonUI(L"ZASTOSUJ", BTN_SCALE, 52);
	m_bBack = new ButtonUI(L"WRÓÆ", BTN_SCALE, 60);
	m_FullScreen = new CheckBoxUI("checkbox", "checkbox-checked", { 2.f, 2.f });
	m_FsText = new TextUI(L"PE£NY EKRAN", "joystix", 32);

	m_HeaderText->set_tcolor({ 229, 198, 0, 255 });
	m_ResText->set_tcolor({ 229, 198, 0, 255 });
	m_HeaderText->center_x(.03f);
	m_ResText->center_x(.27f);
	m_bBack->center_x(.85f);
	m_bApply->center_x(.7f);
	
	m_FsText->center_x(.17f);
	m_FullScreen->set_position({ m_FsText->get_position().x + m_FsText->get_size().x + .015f, .17f });
	m_FsText->shift({ -.01f, .02f });

	m_AppConfig = Window::get_app_config();

	if (m_AppConfig.fullscreen)
		m_FullScreen->select();

	m_FullScreen->on_change([&](bool checked) {
		m_AppConfig.fullscreen = checked;
	});

	m_ResolutionSelect = new SelectListUI({ .37f, .05f }, 5, [&](ListElement *position) {
		auto res = utils::str_split(position->get_value(), ' ');
		m_AppConfig.screen_width = atoi(res[0].c_str());
		m_AppConfig.screen_height = atoi(res[1].c_str());
	});

	for (const auto& res : supported_resolutions) {
		std::string sw = std::to_string(res[0]), sh = std::to_string(res[1]);
		std::wstring sww = std::to_wstring(res[0]), swh = std::to_wstring(res[1]);
		auto rs = m_ResolutionSelect->add_element(sww + L" x " + swh, sw + " " + sh);
		if (res[0] == m_AppConfig.screen_width && res[1] == m_AppConfig.screen_height) {
			if (rs != nullptr)
				rs->select();
		}
	}
	m_ResolutionSelect->center_x(.35f);

	make_entity(m_Background);
	make_entity(m_HeaderText);
	make_entity(m_ResText);
	make_entity(m_FullScreen);
	make_entity(m_FsText);
	make_entity(m_bBack);
	make_entity(m_bApply);
	make_entity(m_ResolutionSelect);
}

Options::~Options()
{
}
