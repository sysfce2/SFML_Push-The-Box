#include "State.h"
#include "UIElement.h"
#include "UIButton.h"

class StateMainMenu : public State
{
private:
	void update(const float& dt) override;
public:
	StateMainMenu();
	virtual ~StateMainMenu();

private:
	UIElement* m_Title;
	UIButton* m_PlayButton;
	UIButton* m_OptionsButton;
	UIButton* m_ExitButton;
};