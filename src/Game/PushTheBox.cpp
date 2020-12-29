#include "PushTheBox.h"
#include "MainMenu.h"

bool PushTheBox::on_init()
{
	uint8_t load_ok = 1;
	auto& manager = AssetsManager::get();

	load_ok *= manager.load_texture("title-logo.png", "title", false);
	load_ok *= manager.load_texture("menu-state.png", "menu-state", false);
	load_ok *= manager.load_texture("btn-4x1.png", "btn-4x1", false);
	load_ok *= manager.load_texture("btn-4x1-pressed.png", "btn-4x1-pressed", false);
	load_ok *= manager.load_texture("btn-3x1.png", "btn-3x1", false);
	load_ok *= manager.load_texture("btn-3x1-pressed.png", "btn-3x1-pressed", false);
	load_ok *= manager.load_texture("btn-1x1.png", "btn-1x1", false);
	load_ok *= manager.load_texture("btn-1x1-pressed.png", "btn-1x1-pressed", false);
	load_ok *= manager.load_texture("header-state.png", "header-state", false);

	load_ok *= manager.load_texture("completed.png", "completed", false);
	load_ok *= manager.load_texture("not-completed.png", "not-completed", false);
	load_ok *= manager.load_texture("play-btn.png", "play-btn", false);
	load_ok *= manager.load_texture("play-btn-pressed.png", "play-btn-pressed", false);

	load_ok *= manager.load_texture("editor-btn.png", "editor-btn", false);
	load_ok *= manager.load_texture("editor-btn-pressed.png", "editor-btn-pressed", false);
	load_ok *= manager.load_texture("editor-level-name.png", "level-name", false);
	load_ok *= manager.load_texture("editor-level-size.png", "level-size", false);
	load_ok *= manager.load_texture("cursor.png", "cursor", false);
	load_ok *= manager.load_texture("plus.png", "plus", false);
	load_ok *= manager.load_texture("minus.png", "minus", false);
	load_ok *= manager.load_texture("editor-storage.png", "editor-storage", true);
	load_ok *= manager.load_texture("editor-state.png", "editor-state", false);
	load_ok *= manager.load_texture("editor-empty-tile.png", "editor-empty-tile", false);
	load_ok *= manager.load_texture("editor-tool-selection.png", "editor-tool-selection", true);

	load_ok *= manager.load_texture("gameplay-background.png", "gameplay-background", true);
	load_ok *= manager.load_texture("gameplay-menu.png", "gameplay-menu", true);
	load_ok *= manager.load_texture("arrow_up.png", "arrow_up", false);
	load_ok *= manager.load_texture("arrow_down.png", "arrow_down", false);
	load_ok *= manager.load_texture("arrow_right.png", "arrow_right", false);
	load_ok *= manager.load_texture("arrow_left.png", "arrow_left", false);

	load_ok *= manager.load_texture("player-spritesheet.png", "player-sprite-sheet", true);
	load_ok *= manager.load_texture("wall.png", "wall0", true);
	load_ok *= manager.load_texture("wall1.png", "wall1", true);
	load_ok *= manager.load_texture("storage.png", "storage", true);
	load_ok *= manager.load_texture("box.png", "box", true);
	load_ok *= manager.load_texture("box-gold.png", "box-gold", true);
	load_ok *= manager.load_texture("floor.png", "floor0", true);
	/*load_ok *= manager.load_texture("floor1.png", "floor1", true);
	load_ok *= manager.load_texture("floor2.png", "floor2", true);
	load_ok *= manager.load_texture("floor3.png", "floor3", true);
	load_ok *= manager.load_texture("floor4.png", "floor4", true);*/

	load_ok *= manager.load_font("joystix.ttf", "joystix");
	load_ok *= manager.load_font("invasion.ttf", "invasion");

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
