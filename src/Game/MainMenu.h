#include "State/State.h"
#include "UI/UIElement.h"
#include "UI/UIButton.h"

class MainMenu : public State
{
private:
	void update(const float& dt) override;
public:
	MainMenu();
	virtual ~MainMenu();

private:
	UIElement* m_Background;
	UIElement* m_Title;
	UIButton* m_PlayButton;
	UIButton* m_OptionsButton;
	UIButton* m_ExitButton;
	UIElement* m_Footer;
};