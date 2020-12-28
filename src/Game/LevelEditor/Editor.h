#pragma once
#include "State/State.h"
#include "UI/UIButton.h"

struct Rect
{
	vec2f pos;
	vec2f size;
};

class Editor : public State
{
private:
	void update(const float& dt) override;
public:
	Editor(std::string file_name, vec2u size);
	virtual ~Editor() = default;
private:
	std::string m_FileName;
	vec2u m_LevelSize;
	Rect m_CanvasRect;

	UIElement* m_Background;
	UIElement* m_Canvas;
	UIText* m_HeaderText;
};