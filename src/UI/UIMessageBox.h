#pragma once
#include "UIButton.h"

class UIMessageBox : public UIElement
{
private:
	void update(const float& dt) override;
public:
	void set_header_text(const std::string& text, uint16_t font_size, float y_pos=.05f);
	void set_message(const std::string& msg, uint16_t font_size, float y_pos = .15f);

	UIMessageBox(const std::string& msgbox_asset, const vec2f& scale);
	virtual ~UIMessageBox() = default;

private:
	UIText* m_HeaderText = nullptr;
	UIText* m_Message = nullptr;
	UIButton* m_bOk = nullptr;
	UIButton* m_bCancel = nullptr;
};