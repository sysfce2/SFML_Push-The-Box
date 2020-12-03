#include "UI/UIText.h"
#include "Core/AssetsManager.h"
#include "Core/Window.h"
#include "Core/Logger.h"

void UIText::update(const float& dt)
{
}

void UIText::render(sf::RenderTarget& target, const vec2f& camera_offset)
{
	if (m_Visible && m_Text != nullptr) {
		vec2f position = get_position_px();
		vec2f camera_pos = camera_offset * Window::size();
		vec2f draw_pos = position - camera_pos - m_Margin;
		if (m_AttachedToEntity != nullptr)
			draw_pos += m_AttachedToEntity->get_position_px();
		m_Text->setPosition(draw_pos);
		target.draw(*m_Text);
	}
}

void UIText::set_text(const std::wstring& text, const std::string& font, uint8_t font_size)
{
	if (m_Text != nullptr)
		delete m_Text;
	sf::Font* font_ptr = AssetsManager::get().get_font(font);
	m_Text = new sf::Text();
	m_Text->setFont(*font_ptr);
	m_Text->setCharacterSize(font_size);
	m_Text->setScale(Window::res_scale());
	m_Text->setString(text);
	m_SizePx = { (float)m_Text->getLocalBounds().width, (float)m_Text->getLocalBounds().height };
	m_Size = m_SizePx / Window::size();
	m_Margin.x = m_Text->getLocalBounds().left * Window::res_scale().x;
	m_Margin.y = m_Text->getLocalBounds().top* Window::res_scale().y;
	if (!m_AntiAliasing)
		const_cast<sf::Texture&>(font_ptr->getTexture(font_size)).setSmooth(false);
}

void UIText::set_color(sf::Color color)
{
	m_Text->setFillColor(color);
}

UIText::UIText(const std::string& text, const std::string& font, uint8_t font_size)
	: UIElement(std::string(), { 1.f, 1.f })
{
	set_text(std::wstring(text.begin(), text.end()), font, font_size);
}

UIText::UIText(const std::wstring& text, const std::string& font, uint8_t font_size)
	: UIElement(std::string(), { 1.f, 1.f })
{
	set_text(text, font, font_size);
}

UIText::~UIText()
{
	delete m_Text;
}
