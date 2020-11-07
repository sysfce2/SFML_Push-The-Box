#include "UIText.h"
#include "AssetsManager.h"
#include "WindowHandle.h"

void UIText::update(const float& dt)
{
}

void UIText::render(sf::RenderTarget& target, const vec2f& camera_offset)
{
	if (m_Visible && m_Text != nullptr) {
		vec2f attach_pos = { 0.f, 0.f };
		if (m_AttachedEntity != nullptr)
			attach_pos = m_AttachedEntity->get_position_px();
		vec2f draw_pos = { attach_pos.x + m_PositionPx.x - camera_offset.x * WindowHandle::width(),
			attach_pos.y + m_PositionPx.y - camera_offset.y * WindowHandle::height() };
		m_Text->setPosition(draw_pos);
		target.draw(*m_Text);
	}
}

void UIText::set_text(const std::string& text, const std::string& font, uint8_t font_size)
{
	if (m_Text != nullptr)
		delete m_Text;
	m_Text = new sf::Text();
	m_Text->setFont(*AssetsManager::get_font(font));
	m_Text->setCharacterSize(font_size);
	m_Text->setScale(vec2f(WindowHandle::get_ratio().x, WindowHandle::get_ratio().y));
	m_Text->setString(text);
}

void UIText::set_color(sf::Color color)
{
	m_Text->setFillColor(color);
}

UIText::UIText(const std::string& text, const std::string& font, uint8_t font_size)
	: UIElement(std::string(), vec2f(1.f, 1.f))
{
	set_text(text, font, font_size);
}

UIText::~UIText()
{
	delete m_Text;
}
