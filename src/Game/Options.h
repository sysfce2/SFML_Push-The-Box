#pragma once
#include "State/State.h"
#include "UI/ButtonUI.h"
#include "UI/TextUI.h"
#include "UI/SelectListUI.h"
#include "UI/TextBoxUI.h"
#include "UI/CheckBoxUI.h"
#include "Core/Window.h"

class Options : public State
{
private:
	AppConfig m_AppConfig;
	void update(const float& dt) override;
public:
	Options();
	virtual ~Options();
	SelectListUI* m_ResolutionSelect;
	ElementUI* m_Background;
	TextUI* m_HeaderText;
	TextUI* m_ResText;
	TextUI* m_FsText;
	ButtonUI* m_bApply;
	ButtonUI* m_bBack;
	CheckBoxUI* m_FullScreen;
};

