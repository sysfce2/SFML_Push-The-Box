#include "EntityState/State.h"
#include "UI/UIElement.h"
#include "UI/UIButton.h"

class StateMainMenu : public State
{
private:
	void update(const float& dt) override;
public:
	StateMainMenu();
	virtual ~StateMainMenu();

private:
	UIElement* m_Background;
	UIElement* m_Title;
	UIButton* m_PlayButton;
	UIButton* m_OptionsButton;
	UIButton* m_ExitButton;
};