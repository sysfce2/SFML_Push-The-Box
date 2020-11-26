#pragma once
#include "UIElement.h"

class UIText : public UIElement
{
private:
	void update(const float& dt) override;
	void render(sf::RenderTarget& target, const vec2f& camera_offset) override;
public:
	void set_text(const std::wstring& text, const std::string& font, uint8_t font_size);
	void set_color(sf::Color color);

	UIText(const std::string& text, const std::string& font, uint8_t font_size);
	UIText(const std::wstring& text, const std::string& font, uint8_t font_size);
	virtual ~UIText();

	// Deleted methods
	void set_scale(const vec2f& scale) = delete;
	void set_sprite(const std::string& asset_id, int x, int y, int w, int h) = delete;
private:
	vec2f m_Margin;
	sf::Text* m_Text = nullptr;
	bool m_AntiAliasing = false;
};