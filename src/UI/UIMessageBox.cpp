#include "UIMessageBox.h"

void UIMessageBox::update(const float& dt)
{
}

void UIMessageBox::set_header_text(const std::string& text, uint16_t font_size, float y_pos)
{
	if (m_HeaderText == nullptr) {

	}
}

void UIMessageBox::set_message(const std::string& msg, uint16_t font_size, float y_pos)
{
}

UIMessageBox::UIMessageBox(const std::string& msgbox_asset, const vec2f& scale)
	: UIElement(msgbox_asset, scale)
{
	center_x().center_y();
}
