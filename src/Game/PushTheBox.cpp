#include "PushTheBox.h"
#include "MainMenu.h"

bool PushTheBox::on_init()
{
	uint8_t load_ok = 1;
	auto& manager = AssetsManager::get();
	load_ok *= manager.load_texture("title-logo.png", "title", false);
	load_ok *= manager.load_texture("menu-state.png", "menu-state", false);
	load_ok *= manager.load_texture("button.png", "button", false);
	load_ok *= manager.load_texture("button-pressed.png", "button-pressed", false);

	load_ok *= manager.load_texture("play-btn.png", "play-btn", false);
	load_ok *= manager.load_texture("play-btn-pressed.png", "play-btn-pressed", false);
	load_ok *= manager.load_texture("select-state.png", "select-state", false);
	load_ok *= manager.load_texture("completed.png", "completed", false);
	load_ok *= manager.load_texture("not-completed.png", "not-completed", false);

	load_ok *= manager.load_texture("player-spritesheet.png", "player-sprite-sheet", true);
	load_ok *= manager.load_texture("wall.png", "wall0", true);
	load_ok *= manager.load_texture("wall1.png", "wall1", true);
	load_ok *= manager.load_texture("target.png", "target", true);
	load_ok *= manager.load_texture("box.png", "box", true);
	load_ok *= manager.load_texture("box-gold.png", "box-gold", true);
	load_ok *= manager.load_texture("floor.png", "floor0", true);
	load_ok *= manager.load_texture("floor1.png", "floor1", true);
	load_ok *= manager.load_texture("floor2.png", "floor2", true);
	load_ok *= manager.load_texture("floor3.png", "floor3", true);
	load_ok *= manager.load_texture("floor4.png", "floor4", true);

	load_ok *= manager.load_font("joystix.ttf", "joystix");
	load_ok *= manager.load_font("INVASION2000.TTF", "invasion");

	if (!load_ok) {
		m_InitErrorMessage = "Failed to load game resources";
		return false;
	}

	StatesManager::get().create_active_state(new MainMenu());

	return true;
}

bool PushTheBox::on_update(const float& dt)
{
	return true;
}
