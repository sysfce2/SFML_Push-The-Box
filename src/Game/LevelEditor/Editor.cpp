#include "Editor.h"
#include "Core/Window.h"
#include "Core/Logger.h"
#include "State/StatesManager.h"

#include <fstream>

EditorValues Editor::Values;

void Editor::update(const float& dt)
{
	if (Values.camera_changed)
		Values.camera_changed = false;

	using KB = sf::Keyboard;

	if (Window::is_focused()) {
		const vec2f camera_speed = { .5f, .88889f };
		float offset = 0.f;

		if (!m_CameraInfo.locked.x) {
			CameraBorders borders = GameCamera::get_cam_borders();

			if (KB::isKeyPressed(KB::Right)) {

				offset = camera_speed.x * dt;
				if (m_Camera.x + offset > borders.bot_right.x)
					m_Camera.x = borders.bot_right.x;
				else m_Camera.x += offset;
			}

			if (KB::isKeyPressed(KB::Left)) {

				offset = -camera_speed.x * dt;
				if (m_Camera.x + offset < borders.top_left.x)
					m_Camera.x = borders.top_left.x;
				else m_Camera.x += offset;
			}
		}
		
		if (!m_CameraInfo.locked.y) {
			CameraBorders borders = GameCamera::get_cam_borders();

			if (KB::isKeyPressed(KB::Up)) {

				offset = -camera_speed.y * dt;
				if (m_Camera.y + offset < borders.top_left.y)
					m_Camera.y = borders.top_left.y;
				else m_Camera.y += offset;
			}

			if (KB::isKeyPressed(KB::Down)) {

				offset = camera_speed.y * dt;
				if (m_Camera.y + offset > borders.bot_right.y)
					m_Camera.y = borders.bot_right.y;
				else m_Camera.y += offset;
			}
		}

		if (offset != 0.f)
			Values.camera_changed = true;

		if (m_bSave->was_pressed())
			save_level();

		if (m_bExit->was_pressed())
			destroy_state();
	}
}

void Editor::save_level()
{
	bool valid = true;
	std::wstring result;
	std::vector<std::wstring> info;
	if (!Values.player_placed) {
		info.emplace_back(L"-Nie ustawiono spawnu gracza");
		valid = false;
	}
	
	if (Values.boxes_placed != Values.boxes_placed) {
		info.emplace_back(L"-Liczba skrzynek nie jest r�wna liczbie magazyn�w");
		valid = false;
	}

	if (Values.boxes_placed == 0) {
		info.emplace_back(L"-Nie postawiono �adnej skrzynki");
		valid = false;
	}

	if (Values.storages_placed == 0) {
		info.emplace_back(L"-Nie postawiono �adnego magazynu");
		valid = false;
	}

	if (valid) {
		std::string path = "levels/custom/" + m_FileName + ".lvl";
		std::ofstream output(path, std::ios_base::out | std::ios_base::binary);
		if (output.is_open()) {

			output.write((char*)&m_LevelSize, sizeof(vec2u));
			output.write((char*)&Values.player->m_TilePos, sizeof(vec2u));
			output.write((char*)&Values.boxes_placed, sizeof(uint16_t));

			for (auto& cols : m_Tiles) for (auto& tile : cols)
				if (tile->m_HasStorage)
					output.write((char*)&tile->m_TilePos, sizeof(vec2u));
			
			for (auto& cols : m_Tiles) for (auto& tile : cols) {
				uint8_t tile_id;
				if (tile->m_HasBox)
					tile_id = BOX_TILE;
				else
					tile_id = tile->m_TileId;
				output.put(tile_id);
			}
		}
		output.close();
		result = L"Poziom zosta� pomy�lnie zapisany!";
		StatesManager::get().create_active_state(new OnSave(result, info));
	}
	else {
		result = L"Wyst�pi�y problemy podczas zapisu poziomu:";
		StatesManager::get().create_active_state(new OnSave(result, info));
	}

}

Editor::Editor(std::string file_name, vec2u size)
	: m_FileName(file_name), m_LevelSize(size)
{
	// Camera
	vec2f total_size = (vec2f)m_LevelSize * Tile(&m_Camera, vec2u()).get_size();
	GameCamera::set_cam_info(total_size, Values.canvas_rect);
	GameCamera::set_cam_borders(total_size, Values.canvas_rect);
	m_CameraInfo = GameCamera::get_cam_info();
	m_Camera = m_CameraInfo.pos;

	// Initialize
	m_Canvas = new ElementUI();
	m_ToolBox = new ToolBox();
	m_Background = new ElementUI("editor-state", { 1.5f, 1.5f });
	m_HeaderText = new TextUI(L"EDYTOR", "joystix", 80);
	m_bSave = new ButtonUI(L"ZAPISZ", { 4.2f, 4.2f }, 42);
	m_bExit = new ButtonUI(L"WYJD�", { 4.2f, 4.2f }, 42);

	std::wstring info_text = L"[RUCH KAMERY: STRZA�KI]  ";
	info_text += L"[RYSOWANIE: LEWY PRZYCISK MYSZY]  ";
	info_text += L"[GUMKA: PRAWY PRZYCISK MYSZY]";
	m_Info = new TextUI(info_text, "joystix", 25);

	Values.player = new Tile(&m_Camera, { 0u, 0u }, PLAYER_TILE);
	Values.player->vanish(true);

	auto& canvas = Values.canvas_rect;
	m_Canvas->set_size(canvas.size).set_position(canvas.pos);
	m_Canvas->set_color({ 16, 16, 55, 255 });
	m_HeaderText->set_tcolor({ 229, 198, 0, 255 });
	m_HeaderText->attach_position(m_ToolBox).center_x(-.115f);
	m_bSave->attach_position(m_ToolBox).center_x(.53f);
	m_bExit->attach_position(m_ToolBox).center_x(.67f);
	m_Info->center_x(.96f);

	// Construct tiles
	m_Tiles.reserve(size.x);
	for (uint16_t i = 0; i < size.x; i++) {
		m_Tiles.emplace_back(std::vector<Tile*>());
		m_Tiles.back().reserve(size.y);
		for (uint16_t j = 0; j < size.y; j++)
			m_Tiles.back().emplace_back(new Tile(&m_Camera, { i, j }));
		if (i == 0) m_TileSize = m_Tiles.back().back()->get_size();
	}

	// Make canvas
	make_entity(m_Canvas);
	for (auto& cols : m_Tiles)
		for (auto& tile : cols)
			make_entity(tile);
	make_entity(Values.player);

	// Make UI
	make_entity(m_Background);
	make_entity(m_HeaderText);
	make_entity(m_ToolBox);
	make_entity(m_bSave);
	make_entity(m_bExit);
	make_entity(m_Info);
}

ToolBox::ToolBox()
{
	const Rect& canvas = Editor::Values.canvas_rect;
	set_position({ canvas.pos.x + canvas.size.x + .02f, .15f });
	set_size({ .25f, .5f });
	set_color(sf::Color(22, 19, 69, 255));

	vec2f btn_scale = { 2.f, 2.f };
	m_tBoxCount = new TextUI(L"ILO�� SKRZYNEK: " + std::to_wstring(Editor::Values.boxes_count), "joystix", 28);
	m_tTiles = new TextUI(L"KAFELKI", "joystix", 28);
	m_BoxPlus = new ButtonUI("", btn_scale);
	m_BoxMinus = new ButtonUI("", btn_scale);
	m_tPlayer = new TextUI(L"GRACZ", "joystix", 28);
 
	m_tBoxCount->attach_position(this).center_x(.03f);
	m_BoxPlus->assign_button_sprite("btn-1x1", "btn-1x1-pressed");
	m_BoxMinus->assign_button_sprite("btn-1x1", "btn-1x1-pressed");
	m_BoxPlus->set_symbol(new ElementUI("plus", btn_scale));
	m_BoxMinus->set_symbol(new ElementUI("minus", btn_scale));
	m_BoxMinus->attach_position(this).set_position({.085f, .08f });
	m_BoxPlus->attach_position(this).set_position({.135f, .08f });
	m_tTiles->attach_position(this).center_x(.2f);
	

	float offset = .0233336f;
	uint8_t current = FLOOR_TILE;
	vec2f place_pos = { offset, m_tTiles->get_position().y + .05f };
	std::vector<std::string> tool_names{ "floor0", "wall0", "box", "storage" };

	for (auto& tool_name : tool_names) {
		Tool* tool = new Tool(current, tool_name);
		tool->m_CanBeUnchecked = false;
		tool->attach_position(this).set_position(place_pos);
		m_Tools.emplace_back(tool);
		place_pos.x += tool->get_size().x + offset;
		current++;
	}

	m_tPlayer->attach_position(this).center_x(place_pos.y + .13f);
	Tool* player_tile = new Tool(PLAYER_TILE, "box");
	player_tile->set_sprite("player-sprite-sheet", { 0, 0 }, { 64, 64 });
	player_tile->m_CanBeUnchecked = false;
	player_tile->attach_position(this).center_x(place_pos.y + .17f);
	m_Tools.emplace_back(player_tile);
	m_Tools.front()->select();

	for (auto& tool : m_Tools) {
		tool->on_change([&](bool is_selected) {
			for (auto& t : m_Tools)
				if (tool != t) t->select(false);
			Editor::Values.selected_tool = tool->m_TileId;
		});
		add_child_entity(tool);
	}

	add_child_entity(m_tBoxCount);
	add_child_entity(m_BoxPlus);
	add_child_entity(m_BoxMinus);
	add_child_entity(m_tTiles);
	add_child_entity(m_tPlayer);
}

void ToolBox::update(const float& dt)
{
	auto& val = Editor::Values;
	auto update_box_count = [&]() -> void {
		m_tBoxCount->set_text(L"ILO�� SKRZYNEK: " + std::to_wstring(val.boxes_count));
		m_tBoxCount->center_x();
	};

	if (m_BoxPlus->was_pressed()) {
		val.boxes_count++;
		update_box_count();
	}

	if (m_BoxMinus->was_pressed()) {
		if (val.boxes_count > 1) {
			val.boxes_count--;
			update_box_count();
		}
	}

	uint16_t placed[3] = { val.boxes_placed, val.storages_placed, val.player_placed };
	uint16_t count[3] = { val.boxes_count, val.boxes_count, 1 };
	
	for (uint8_t i = 0; i < 3; i++) {
		Tool* tool = m_Tools.at(i + 2);
		if (placed[i] >= count[i]) {
			if (!tool->is_disabled()) {
				tool->disable();
				val.selected_tool = NONE_TILE;
			}
		}
		else if (tool->is_disabled())
			tool->disable(false);
	}
}

Tile::Tile(vec2f* camera, vec2u tile_pos, uint8_t id)
	: m_CameraPtr(camera), m_TilePos(tile_pos), m_TileId(id)
{
	if (id == PLAYER_TILE) 
		set_sprite("player-sprite-sheet", { 0, 0 }, { 64, 64 });
	else {
		set_sprite("editor-empty-tile");
		set_color({ 255,255,255,230 });
	}

	set_scale({ 1.2f, 1.2f });
	set_position(get_size() * (vec2f)tile_pos);
}

void Tile::update(const float& dt)
{
	if (Editor::Values.camera_changed) {
		vec2f screen_pos = get_position() - *m_CameraPtr;
		vec2f size = get_size();
		const Rect& canvas = Editor::Values.canvas_rect;
		if ((screen_pos.x + size.x >= canvas.pos.x
			&& screen_pos.x <= canvas.pos.x + canvas.size.x)
			&& (screen_pos.y + size.y >= canvas.pos.y
			&& screen_pos.y <= canvas.pos.y + canvas.size.y)) {
			if (!is_visible()) appear();
		}
		else if (is_visible()) vanish();
	}

	if (Window::is_focused() && is_visible() && m_TileId != PLAYER_TILE) {
		sf::FloatRect bounds = m_Sprite->getGlobalBounds();
		sf::Vector2i mouse = sf::Mouse::getPosition(*Window::get_handle());
	
		bool is_selected = bounds.contains((float)mouse.x, (float)mouse.y);
		if (is_selected != m_IsSelected)
			select(is_selected);

		if (is_selected) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (m_lMButtonReleased) {
					set_tile(Editor::Values.selected_tool);
					m_lMButtonReleased = false;
				}
			}
			else if (!m_lMButtonReleased) m_lMButtonReleased = true;

			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				if (m_rMButtonReleased) {
					set_tile(ERASER);
					m_rMButtonReleased = false;
				}
			}
			else if (!m_rMButtonReleased) m_rMButtonReleased = true;
		}
		else {
			if (!m_lMButtonReleased) m_lMButtonReleased = true;
			if (!m_rMButtonReleased) m_rMButtonReleased = true;
		}
	}
}

void Tile::select(bool selected)
{
	m_IsSelected = selected;
	if (m_TileId != PLAYER_TILE && Editor::Values.player_placed)
		if (m_TilePos == Editor::Values.player->m_TilePos)
			Editor::Values.player->select(selected);

	if (selected)
		set_color(sf::Color(100, 220, 0, 255));
	else
		set_color(sf::Color(255, 255, 255, m_TileId != NONE_TILE ? 255 : 230));
}

void Tile::set_tile(uint8_t tile_id)
{
	if (tile_id != m_TileId) {

		auto& val = Editor::Values;
		auto remove_storage = [&]() -> void {
			if (m_HasStorage) val.storages_placed--;
			m_HasStorage = false;
		};
		auto remove_box = [&]() -> void {
			if (m_HasBox) val.boxes_placed--;
			m_HasBox = false;
		};
		
		switch (tile_id) {
		case ERASER:
			if (m_TileId != NONE_TILE) {
				if (m_HasPlayer) {
					m_HasPlayer = false;
					val.player_placed = false;
					val.player->vanish(true);
				}
				else if (m_HasStorage && !m_HasBox) {
					set_sprite("floor0");
					remove_storage();
				}
				else if (m_HasBox) {
					if (m_HasStorage)
						set_sprite("editor-storage");
					else set_sprite("floor0");
					remove_box();
					m_TileId = FLOOR_TILE;
				}
				else {
					set_sprite("editor-empty-tile");
					m_TileId = NONE_TILE;
				}
			}
			break;
		case NONE_TILE:
			break;
		case FLOOR_TILE:
			if (!m_HasBox && !m_HasStorage && !m_HasPlayer) {
				set_sprite("floor0");
				m_TileId = tile_id;
			}
			break;
		case WALL_TILE:
			if (!m_HasPlayer) {
				set_sprite("wall0");
				remove_box();
				remove_storage();
				m_TileId = tile_id;
			}
			break;
		case BOX_TILE:
			if (m_TileId == FLOOR_TILE && !m_HasBox && !m_HasPlayer
				&& val.boxes_placed < val.boxes_count) {
				val.boxes_placed++;
				if (m_HasStorage) set_sprite("box-gold");
				else set_sprite("box");
				m_HasBox = true;
				m_TileId = tile_id;
			}
			break;
		case STORAGE_TILE:
			if ((m_TileId == FLOOR_TILE || m_TileId == BOX_TILE) && !m_HasStorage)
				if( val.storages_placed < val.boxes_count) {
					val.storages_placed++;
					if (m_HasBox) set_sprite("box-gold");
					else set_sprite("editor-storage");
					m_HasStorage = true;
					m_TileId = FLOOR_TILE;
				}
			break;
		case PLAYER_TILE:
			if (m_TileId == FLOOR_TILE && !m_HasBox && !val.player_placed) {
				val.player_placed = true;
				val.player->m_TilePos = m_TilePos;
				val.player->set_position(get_size() * (vec2f)m_TilePos);
				val.player->appear();
				m_HasPlayer = true;
			}
			break;
		}

		select(m_IsSelected);
	}
}

Tool::Tool(uint8_t id, const std::string& sprite)
	: CheckBoxUI(sprite, "editor-tool-selection"), m_TileId(id)
{
}

void OnSave::update(const float& dt)
{
	if (m_bBack->was_pressed())
		destroy_state();
}

OnSave::OnSave(std::wstring result, std::vector<std::wstring> info)
{
	ElementUI* background = new ElementUI("header-state", { 1.5f, 1.5f });
	TextUI* header = new TextUI(L"EDYTOR POZIOM�W", "joystix", 80);
	m_bBack = new ButtonUI(L"WR��", { 4.5f, 4.5f }, 60);
	
	header->set_tcolor({ 229, 198, 0, 255 });
	header->center_x(.017f);
	make_entity(background);
	make_entity(header);
	
	float y_pos = (info.size() > 0) ? .3f : .4f;
	TextUI* t_result = new TextUI(result, "joystix", 48);
	t_result->center_x(y_pos);
	make_entity(t_result);
	
	int j = 0;
	if (info.size() > 0) y_pos += .1f;
	for (const auto& i : info) {
		TextUI* ti = new TextUI(i, "joystix", 36);
		ti->center_x(y_pos);
		make_entity(ti);
		y_pos += (j == 0) ? .075f : .085f; j++;
	}

	m_bBack->center_x(y_pos + .12f);
	make_entity(m_bBack);
}
