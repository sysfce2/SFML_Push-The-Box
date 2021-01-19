#include "State/State.h"
#include "UI/ElementUI.h"
#include "UI/ButtonUI.h"

class MainMenu : public State
{
private:
	void update(const float& dt) override;
public:
	MainMenu();
	virtual ~MainMenu();

private:
	ElementUI* m_Background;
	ElementUI* m_Title;
	ButtonUI* m_PlayButton;
	ButtonUI* m_OptionsButton;
	ButtonUI* m_ExitButton;
	ElementUI* m_Footer;
};