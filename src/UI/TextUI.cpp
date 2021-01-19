#include "UI/TextUI.h"
#include "Core/AssetsManager.h"
#include "Core/Window.h"
#include "Core/Logger.h"

void TextUI::update(const float& dt)
{
}

void TextUI::render(sf::RenderTarget& target, const vec2f& camera)
{
	if (m_Visible && m_Text != nullptr) {
		vec2f draw_pos = get_position_px() - m_Margin;
		if (m_UseCameraPosition)
			draw_pos -= camera * Window::size();

		Entity* entity = get_attached();
		while (entity != nullptr) {
			draw_pos += entity->get_position_px();
			entity = entity->get_attached();
		}
			
		m_Text->setPosition(draw_pos);
		target.draw(*m_Text);
	}
}

void TextUI::set_text(const std::wstring& text, const std::string& font, uint8_t font_size)
{
	if (m_Text != nullptr)
		delete m_Text;

	if (font.length() > 0)
		m_Font = AssetsManager::get().get_font(font);

	if (font_size > 0)
		m_FontSize = font_size;

	if (m_Font != nullptr) {
		m_TextContent = text;
		m_Text = new sf::Text();
		m_Text->setFont(*m_Font);
		m_Text->setCharacterSize(m_FontSize);
		m_Text->setScale(Window::res_scale());
		m_Text->setString(m_TextContent);
		m_Text->setFillColor(m_Color);
		
		vec2f size = { (float)m_Text->getLocalBounds().width, (float)m_Text->getLocalBounds().height };
		m_SizePx = size * Window::res_scale();
		m_Size = m_SizePx / Window::size();
		m_Margin.x = m_Text->getLocalBounds().left * Window::res_scale().x;
		m_Margin.y = m_Text->getLocalBounds().top * Window::res_scale().y;
		if (!m_AntiAliasing)
			const_cast<sf::Texture&>(m_Font->getTexture(m_FontSize)).setSmooth(false);
	}
	else
		LOG_ERROR("Trying to set text with no proper font assigned. Font name:", font);
}

void TextUI::set_tcolor(const sf::Color& color)
{
	m_Color = color;
	m_Text->setFillColor(m_Color);
}

void TextUI::use_camera_position(bool use)
{
	m_UseCameraPosition = use;
}

TextUI::TextUI(const std::string& text, const std::string& font, uint8_t font_size)
	: ElementUI(std::string(), { 1.f, 1.f })
{
	set_text(std::wstring(text.begin(), text.end()), font, font_size);
}

TextUI::TextUI(const std::wstring& text, const std::string& font, uint8_t font_size)
	: ElementUI(std::string(), { 1.f, 1.f })
{
	set_text(text, font, font_size);
}

TextUI::~TextUI()
{
	delete m_Text;
}
