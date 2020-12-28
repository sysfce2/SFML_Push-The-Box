#include "Editor.h"

const sf::Color HEADER_COLOR{ 229, 198, 0, 255 };

void Editor::update(const float& dt)
{
}

Editor::Editor(std::string file_name, vec2u size)
	: m_FileName(file_name), m_LevelSize(size)
{
	m_Canvas = new UIElement();
	m_Background = new UIElement("editor-state", { 1.5f, 1.5f });
	m_HeaderText = new UIText(L"EDYTOR", "joystix", 80);
	
	//m_Background->set_color(sf::Color(255, 255, 255, 100));
	m_HeaderText->set_tcolor(HEADER_COLOR);
	m_HeaderText->set_position({ 0.f, .03f }).center_x();
	m_CanvasRect = { {.05f, .15f}, {.65f, .65f} };
	m_Canvas->set_size({ .7f, .75f }).set_position({ 0.025f, .1f });
	m_Canvas->set_color(sf::Color(16, 16, 55, 255));

	make_entity(m_Canvas);
	make_entity(m_Background);
	make_entity(m_HeaderText);
}
