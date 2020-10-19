#include "State.h"
#include "UIButton.h"
#include "MenuTitle.h"

class StateMainMenu : public State
{
private:
	void update(const float& dt);
public:
	StateMainMenu();
	virtual ~StateMainMenu();

private:
	UIButton* m_PlayButton;
	UIButton* m_OptionsButton;
	UIButton* m_ExitButton;
	MenuTitle* m_Title;
};