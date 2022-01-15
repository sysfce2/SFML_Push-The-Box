#pragma once
#include "UI/ElementUI.h"

class TextUI : public ElementUI
{
private:
	void update(const float& dt) override;
	void render(sf::RenderTarget& target, const vec2f& camera) override;
public:
	void refresh() override;
	void set_text(const std::wstring& text, const std::string& font = "", u8 font_size = 0);
	void set_tcolor(const sf::Color& color);
	void use_camera_position(bool use = true);
	inline std::wstring get_content() const { return m_TextContent; }

	TextUI(const std::string& text, const std::string& font, u8 font_size);
	TextUI(const std::wstring& text, const std::string& font, u8 font_size);
	virtual ~TextUI();

	// Deleted entity methods
	Entity& set_sprite(const std::string& asset_id, int x, int y, int w, int h) = delete;
	Entity& set_scale(const vec2f& scale) = delete;
	Entity& set_size(const vec2f& size) = delete;
	Entity& set_size_px(const vec2f& size) = delete;
	Entity& set_color(const sf::Color& color) = delete;

private:
	std::wstring m_TextContent;
	std::string m_FontName;
	vec2f m_Margin;
	u8 m_FontSize = 24;
	sf::Color m_Color{ 255, 255, 255, 255 };
	sf::Font* m_Font = nullptr;
	sf::Text* m_Text = nullptr;
	bool m_AntiAliasing = false;
};