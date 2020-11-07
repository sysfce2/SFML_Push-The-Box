#pragma once
#include "UIElement.h"

class UIText : public UIElement
{
private:
	void update(const float& dt) override;
	void render(sf::RenderTarget& target, const vec2f& camera_offset) override;
public:
	void set_text(const std::string& text, const std::string& font, uint8_t font_size);
	void set_color(sf::Color color);

	// Deleted methods
	void set_scale(const vec2f& scale) = delete;
	void set_sprite(const std::string& asset_id, int x, int y, int w, int h) = delete;

	UIText(const std::string& text, const std::string& font, uint8_t font_size);
	virtual ~UIText();
private:
	sf::Text* m_Text = nullptr;
};