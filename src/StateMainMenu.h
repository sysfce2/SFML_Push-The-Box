#include "State.h"
#include "UIButton.h"

class StateMainMenu : public State
{
private:
	void update(float dt);
public:
	StateMainMenu(AssetsManager* assets_manager);
	virtual ~StateMainMenu();

private:
	UIButton* m_PlayButton;
};