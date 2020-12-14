#pragma once
#include "UI/UIElement.h"

class UIText : public UIElement
{
private:
	void update(const float& dt) override;
	void render(sf::RenderTarget& target, const vec2f& camera) override;
public:
	void set_text(const std::wstring& text, const std::string& font = "", uint8_t font_size = 0);
	void set_color(sf::Color color);
	void use_camera_position(bool use = true);
	inline std::wstring get_content() const { return m_TextContent; }

	UIText(const std::string& text, const std::string& font, uint8_t font_size);
	UIText(const std::wstring& text, const std::string& font, uint8_t font_size);
	virtual ~UIText();

	// Deleted entity methods
	Entity& set_scale(const vec2f& scale) = delete;
	Entity& set_sprite(const std::string& asset_id, int x, int y, int w, int h) = delete;
private:
	std::wstring m_TextContent;
	vec2f m_Margin;
	uint8_t m_FontSize = 24;
	sf::Color m_Color{ 255, 255, 255, 255 };
	sf::Font* m_Font = nullptr;
	sf::Text* m_Text = nullptr;
	bool m_AntiAliasing = false;
	bool m_UseCameraPosition = false;
};