#include "UIText.h"
#include "AssetsManager.h"
#include "WindowHandle.h"
#include "Logger.h"

void UIText::update(const float& dt)
{
}

void UIText::render(sf::RenderTarget& target, const vec2f& camera_offset)
{
	if (m_Visible && m_Text != nullptr) {
		vec2f position = get_position_px();
		vec2f camera_pos = { camera_offset.x * WindowHandle::width(), camera_offset.y * WindowHandle::height() };
		vec2f draw_pos = position - camera_pos - m_Margin;
		if (m_AttachedEntity != nullptr)
			draw_pos += m_AttachedEntity->get_position_px();
		m_Text->setPosition(draw_pos);
		target.draw(*m_Text);
	}
}

void UIText::set_text(const std::string& text, const std::string& font, uint8_t font_size)
{
	if (m_Text != nullptr)
		delete m_Text;
	sf::Font* font_ptr = AssetsManager::get_font(font);
	m_Text = new sf::Text();
	m_Text->setFont(*font_ptr);
	m_Text->setCharacterSize(font_size);
	m_Text->setScale(vec2f(WindowHandle::get_ratio().x, WindowHandle::get_ratio().y));
	m_Text->setString(text);
	m_SizePx = { (float)m_Text->getLocalBounds().width, (float)m_Text->getLocalBounds().height };
	m_Size = { m_SizePx.x / WindowHandle::width(), m_SizePx.y / WindowHandle::height() };
	m_Margin.x = m_Text->getLocalBounds().left * WindowHandle::get_ratio().x;
	m_Margin.y = m_Text->getLocalBounds().top* WindowHandle::get_ratio().y;
	if (!m_AntiAliasing)
		const_cast<sf::Texture&>(font_ptr->getTexture(font_size)).setSmooth(false);
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
