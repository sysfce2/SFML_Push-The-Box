#include "Editor.h"
#include "Core/Window.h"
#include "Core/Logger.h"
#include "State/StatesManager.h"

#include <fstream>

// Consts
constexpr float A_RATIO = 9.f / 16.f;
constexpr float CAMERA_SPEED = .5f;

// Static
const Rect Editor::CanvasRect{ {.03f, .055f}, {.67f, .88f} };
bool Editor::CameraChanged = false;
bool Editor::PlayerPlaced = false;
uint8_t Editor::SelectedTool = FLOOR_TILE;
uint16_t Editor::BoxesPlaced = 0;
uint16_t Editor::StoragesPlaced = 0;
uint16_t Editor::BoxesCount = 4;
Tile* Editor::PlayerTile = nullptr;

void Editor::update(const float& dt)
{
	if (CameraChanged)
		CameraChanged = false;

	if (Window::is_focused()) {
		float offset, border = .5f;
		vec2f before = m_Camera;

		using KB = sf::Keyboard;
		if (KB::isKeyPressed(KB::Up)) {
			offset = -CAMERA_SPEED * dt;
			if (m_Camera.y + offset < -border)
				m_Camera.y = -border;
			else m_Camera.y += offset;
		}
		if (KB::isKeyPressed(KB::Right)) {
			offset = CAMERA_SPEED * dt * A_RATIO;
			float max_x = m_TileSize.x * m_LevelSize.x + border * A_RATIO - .5f;
			if (m_Camera.x + offset > max_x)
				m_Camera.x = max_x;
			else m_Camera.x += offset;
		}
		if (KB::isKeyPressed(KB::Down)) {
			offset = CAMERA_SPEED * dt;
			float max_y = m_TileSize.y * m_LevelSize.y + border - .5f;
			if (m_Camera.y + offset > max_y)
				m_Camera.y = max_y;
			else m_Camera.y += offset;
		}
		if (KB::isKeyPressed(KB::Left)) {
			offset = -CAMERA_SPEED * dt * A_RATIO;
			if (m_Camera.x + offset < -border * A_RATIO)
				m_Camera.x = -border * A_RATIO;
			else m_Camera.x += offset;
		}

		if (m_Camera != before)
			CameraChanged = true;

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
	if (!Editor::PlayerPlaced) {
		info.emplace_back(L"-Nie ustawiono spawnu gracza");
		valid = false;
	}
	
	if (Editor::BoxesPlaced != Editor::StoragesPlaced) {
		info.emplace_back(L"-Liczba skrzynek nie jest równa liczbie magazynów");
		valid = false;
	}

	if (Editor::BoxesPlaced == 0) {
		info.emplace_back(L"-Nie postawiono ¿adnej skrzynki");
		valid = false;
	}

	if (Editor::BoxesPlaced == 0) {
		info.emplace_back(L"-Nie postawiono ¿adnego magazynu");
		valid = false;
	}

	if (valid) {
		std::string path = "levels/custom/" + m_FileName + ".lvl";
		std::ofstream output(path, std::ios_base::out | std::ios_base::binary);
		if (output.is_open()) {

			output.write((char*)&m_LevelSize, sizeof(vec2u));
			output.write((char*)&PlayerTile->m_TilePos, sizeof(vec2u));
			output.write((char*)&BoxesPlaced, sizeof(uint16_t));

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
		result = L"Poziom zosta³ pomyœlnie zapisany!";
		StatesManager::get().create_active_state(new OnSave(result, info));
	}
	else {
		result = L"Wyst¹pi³y problemy podczas zapisu poziomu:";
		StatesManager::get().create_active_state(new OnSave(result, info));
	}

}

Editor::Editor(std::string file_name, vec2u size)
	: m_FileName(file_name), m_LevelSize(size)
{
	// Initialize
	m_Canvas = new UIElement();
	m_ToolBox = new ToolBox();
	m_Background = new UIElement("editor-state", { 1.5f, 1.5f });
	m_HeaderText = new UIText(L"EDYTOR", "joystix", 80);
	m_bSave = new UIButton(L"ZAPISZ", { 4.2f, 4.2f }, 42);
	m_bExit = new UIButton(L"WYJD", { 4.2f, 4.2f }, 42);

	std::wstring info_text = L"[RUCH KAMERY: STRZA£KI]  ";
	info_text += L"[RYSOWANIE: LEWY PRZYCISK MYSZY]  ";
	info_text += L"[GUMKA: PRAWY PRZYCISK MYSZY]";
	m_Info = new UIText(info_text, "joystix", 25);

	PlayerTile = new Tile(&m_Camera, { 0u, 0u }, PLAYER_TILE);
	PlayerTile->vanish(true);

	//m_Background->set_color({ 255,255,255,140 });
	m_Canvas->set_size(CanvasRect.size).set_position(CanvasRect.pos);
	m_Canvas->set_color(sf::Color(16, 16, 55, 255));
	m_HeaderText->set_tcolor({ 229, 198, 0, 255 });
	m_HeaderText->attach_position(m_ToolBox).center_x(-.115f);
	m_bSave->attach_position(m_ToolBox).center_x(.53f);
	m_bExit->attach_position(m_ToolBox).center_x(.67f);
	//m_Info->set_tcolor({ 229, 198, 0, 255 });
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
	make_entity(PlayerTile);

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
	const Rect& canvas = Editor::CanvasRect;
	set_position({ canvas.pos.x + canvas.size.x + .02f, .15f });
	set_size({ .25f, .5f });
	set_color(sf::Color(22, 19, 69, 255));

	vec2f btn_scale = { 2.f, 2.f };
	m_tBoxCount = new UIText(L"ILOŒÆ SKRZYNEK: " + std::to_wstring(Editor::BoxesCount), "joystix", 28);
	m_tTiles = new UIText(L"KAFELKI", "joystix", 28);
	m_BoxPlus = new UIButton("", btn_scale);
	m_BoxMinus = new UIButton("", btn_scale);
	m_tPlayer = new UIText(L"GRACZ", "joystix", 28);
 
	m_tBoxCount->attach_position(this).center_x(.03f);
	m_BoxPlus->assign_button_sprite("btn-1x1", "btn-1x1-pressed");
	m_BoxMinus->assign_button_sprite("btn-1x1", "btn-1x1-pressed");
	m_BoxPlus->set_symbol(new UIElement("plus", btn_scale));
	m_BoxMinus->set_symbol(new UIElement("minus", btn_scale));
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
			Editor::SelectedTool = tool->m_TileId;
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
	auto update_box_count = [&]() -> void {
		m_tBoxCount->set_text(L"ILOŒÆ SKRZYNEK: " + std::to_wstring(Editor::BoxesCount));
		m_tBoxCount->center_x();
	};

	if (m_BoxPlus->was_pressed()) {
		Editor::BoxesCount++;
		update_box_count();
	}

	if (m_BoxMinus->was_pressed()) {
		if (Editor::BoxesCount > 1) {
			Editor::BoxesCount--;
			update_box_count();
		}
	}

	for (uint8_t i = 0; i < 3; i++) {
		uint16_t placed, count;
		Tool* tool = nullptr;
		switch (i) {
		case 0:
			placed = Editor::BoxesPlaced;
			count = Editor::BoxesCount;
			tool = m_Tools.at(2);
			break;
		case 1:
			placed = Editor::StoragesPlaced;
			count = Editor::BoxesCount;
			tool = m_Tools.at(3);
			break;
		case 2:
			placed = Editor::PlayerPlaced;
			count = 1u;
			tool = m_Tools.at(4);
			break;
		}

		if (placed >= count) {
			if (!tool->is_disabled()) {
				tool->disable();
				Editor::SelectedTool = NONE_TILE;
			}
		}
		else if (tool->is_disabled())
			tool->disable(false);
	}
}

const vec2f TILES_START{ 0.22f, 0.22f };
const vec2f TILES_SCALE{ 1.2f, 1.2f };

Tile::Tile(vec2f* camera, vec2u tile_pos, uint8_t id)
	: m_CameraPtr(camera), m_TilePos(tile_pos), m_TileId(id)
{
	if (id == PLAYER_TILE) 
		set_sprite("player-sprite-sheet", { 0, 0 }, { 64, 64 });
	else {
		set_sprite("editor-empty-tile");
		set_color({ 255,255,255,230 });
	}

	set_scale(TILES_SCALE);
	set_position(TILES_START + get_size() * (vec2f)tile_pos);
}

void Tile::update(const float& dt)
{
	if (Editor::CameraChanged) {
		vec2f screen_pos = get_position() - *m_CameraPtr;
		vec2f size = get_size();
		const Rect& canvas = Editor::CanvasRect;
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
					set_tile(Editor::SelectedTool);
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
	if (m_TileId != PLAYER_TILE && Editor::PlayerPlaced)
		if (m_TilePos == Editor::PlayerTile->m_TilePos)
			Editor::PlayerTile->select(selected);

	if (selected)
		set_color(sf::Color(100, 220, 0, 255));
	else
		set_color(sf::Color(255, 255, 255, m_TileId != NONE_TILE ? 255 : 230));
}

void Tile::set_tile(uint8_t tile_id)
{
	if (tile_id != m_TileId) {
		auto remove_storage = [&]() -> void {
			if (m_HasStorage) Editor::StoragesPlaced--;
			m_HasStorage = false;
		};
		auto remove_box = [&]() -> void {
			if (m_HasBox) Editor::BoxesPlaced--;
			m_HasBox = false;
		};

		switch (tile_id) {
		case ERASER:
			if (m_HasPlayer) {
				m_HasPlayer = false;
				Editor::PlayerPlaced = false;
				Editor::PlayerTile->vanish(true);
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
				m_TileId = tile_id;
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
				&& Editor::BoxesPlaced < Editor::BoxesCount) {
				Editor::BoxesPlaced++;
				if (m_HasStorage) set_sprite("box-gold");
				else set_sprite("box");
				m_HasBox = true;
				m_TileId = tile_id;
			}
			break;
		case STORAGE_TILE:
			if ((m_TileId == FLOOR_TILE || m_TileId == BOX_TILE) && !m_HasStorage)
				if( Editor::StoragesPlaced < Editor::BoxesCount) {
					Editor::StoragesPlaced++;
					if (m_HasBox) set_sprite("box-gold");
					else set_sprite("editor-storage");
					m_HasStorage = true;
					m_TileId = FLOOR_TILE;
				}
			break;
		case PLAYER_TILE:
			if (m_TileId == FLOOR_TILE && !m_HasBox && !Editor::PlayerPlaced) {
				Editor::PlayerPlaced = true;
				Editor::PlayerTile->m_TilePos = m_TilePos;
				Editor::PlayerTile->set_position(TILES_START + get_size() * (vec2f)m_TilePos);
				Editor::PlayerTile->appear();
				m_HasPlayer = true;
			}
			break;
		}

		select(m_IsSelected);
	}
}

Tool::Tool(uint8_t id, const std::string& sprite)
	: UICheckBox(sprite, "editor-tool-selection"), m_TileId(id)
{
}

void OnSave::update(const float& dt)
{
	if (m_bBack->was_pressed())
		destroy_state();
}

OnSave::OnSave(std::wstring result, std::vector<std::wstring> info)
{
	UIElement* background = new UIElement("header-state", { 1.5f, 1.5f });
	UIText* header = new UIText(L"EDYTOR POZIOMÓW", "joystix", 80);
	m_bBack = new UIButton(L"WRÓÆ", { 4.5f, 4.5f }, 60);
	
	header->set_tcolor({ 229, 198, 0, 255 });
	header->center_x(.017f);
	make_entity(background);
	make_entity(header);
	
	float y_pos = (info.size() > 0) ? .3f : .4f;
	UIText* t_result = new UIText(result, "joystix", 48);
	t_result->center_x(y_pos);
	make_entity(t_result);
	
	int j = 0;
	if (info.size() > 0) y_pos += .1f;
	for (const auto& i : info) {
		UIText* ti = new UIText(i, "joystix", 36);
		ti->center_x(y_pos);
		make_entity(ti);
		y_pos += (j == 0) ? .075f : .085f; j++;
	}

	m_bBack->center_x(y_pos + .12f);
	make_entity(m_bBack);
}
