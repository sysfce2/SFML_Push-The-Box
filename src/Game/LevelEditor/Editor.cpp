#include "Editor.h"
#include "Core/Window.h"
#include "Core/Logger.h"

// Consts
constexpr float A_RATIO = 9.f / 16.f;
constexpr float CAMERA_SPEED = .5f;
const vec2f TILES_START{ 0.22f, 0.22f};
const vec2f TILES_SCALE{ 1.2f, 1.2f };

// Static
const Rect Editor::CanvasRect{ {.05f, .15f}, {.65f, .65f} };
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

		if (m_bExit->was_pressed())
			destroy_state();
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

	PlayerTile = new Tile(&m_Camera, { 0u, 0u }, PLAYER_TILE);
	PlayerTile->vanish(true);

	m_Canvas->set_size({ .7f, .75f }).set_position({ .025f, .1f });
	m_Canvas->set_color(sf::Color(16, 16, 55, 255));
	m_HeaderText->set_tcolor({ 229, 198, 0, 255 });
	m_HeaderText->set_position({ 0.f, .03f }).center_x();
	m_bSave->attach_position(m_ToolBox).set_position({ .0f, .55f }).center_x();
	m_bExit->attach_position(m_ToolBox).set_position({ .0f, .7f }).center_x();

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
}

ToolBox::ToolBox()
{
	Rect canvas = Editor::CanvasRect;
	set_position({ canvas.pos.x + canvas.size.x + .02f, canvas.pos.y });
	set_size({ .25f, .5f });
	set_color(sf::Color(22, 19, 69, 255));

	vec2f btn_scale = { 2.f, 2.f };
	m_tBoxCount = new UIText(L"ILOŒÆ SKRZYNEK: " + std::to_wstring(Editor::BoxesCount), "joystix", 28);
	m_tTiles = new UIText(L"KAFELKI", "joystix", 28);
	m_BoxPlus = new UIButton("", btn_scale);
	m_BoxMinus = new UIButton("", btn_scale);
	m_tPlayer = new UIText(L"GRACZ", "joystix", 28);
 
	m_tBoxCount->attach_position(this).set_position({ 0.f, .03f }).center_x();
	m_BoxPlus->assign_button_sprite("btn-1x1", "btn-1x1-pressed");
	m_BoxMinus->assign_button_sprite("btn-1x1", "btn-1x1-pressed");
	m_BoxPlus->set_symbol(new UIElement("plus", btn_scale));
	m_BoxMinus->set_symbol(new UIElement("minus", btn_scale));
	m_BoxPlus->attach_position(this).set_position({.08f, .075f });
	m_BoxMinus->attach_position(this).set_position({.13f, .075f });
	m_tTiles->attach_position(this).set_position({ .0f, .2f }).center_x();
	

	float offset = .0233336f;
	uint8_t current = FLOOR_TILE;
	vec2f place_pos = { offset, m_tTiles->get_position().y + .05f };
	std::vector<std::string> tool_names{ "floor0", "wall0", "box", "storage" };

	for (auto& tool_name : tool_names) {
		Tool* tool = new Tool(current, tool_name);
		tool->m_CanBeUnselected = false;
		tool->attach_position(this).set_position(place_pos);
		m_Tools.emplace_back(tool);
		place_pos.x += tool->get_size().x + offset;
		current++;
	}

	m_tPlayer->attach_position(this).set_position({ 0.f, place_pos.y + .13f }).center_x();
	Tool* player_tile = new Tool(PLAYER_TILE, "box");
	player_tile->set_sprite("player-sprite-sheet", { 0, 0 }, { 64, 64 });
	player_tile->m_CanBeUnselected = false;
	player_tile->attach_position(this).set_position({ 0.f, place_pos.y + .17f }).center_x();
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
				m_Tools.front()->select();
				Editor::SelectedTool = FLOOR_TILE;
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
	else set_sprite("editor-empty-tile");

	set_scale(TILES_SCALE);
	set_position(TILES_START + get_size() * (vec2f)tile_pos);
}

void Tile::update(const float& dt)
{
	if (Editor::CameraChanged) {
		vec2f screen_pos = get_position() - *m_CameraPtr;
		vec2f size = get_size();
		Rect canvas = Editor::CanvasRect;
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
					set_tile(NONE_TILE);
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

	if (selected)
		set_color(sf::Color(100, 220, 0, 255));
	else
		set_color(sf::Color(255, 255, 255, 255));

	if (m_TileId != PLAYER_TILE && Editor::PlayerPlaced)
		if (m_TilePos == Editor::PlayerTile->m_TilePos)
			Editor::PlayerTile->select(selected);
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

		if (tile_id == NONE_TILE) {
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
		}
		else if (tile_id == FLOOR_TILE) {
			if (!m_HasBox && !m_HasStorage && !m_HasPlayer) {
				set_sprite("floor0");
				m_TileId = tile_id;
			}
		}
		else if (tile_id == WALL_TILE) {
			set_sprite("wall0");
			remove_box();
			remove_storage();
			m_TileId = tile_id;
		}
		else if (tile_id == BOX_TILE && !m_HasBox) {
			if (Editor::BoxesPlaced < Editor::BoxesCount && m_TileId == FLOOR_TILE) {
				Editor::BoxesPlaced++;
				if (m_HasStorage) set_sprite("box-gold");
				else set_sprite("box");
				m_HasBox = true;
				m_TileId = tile_id;
			}
		}
		else if (tile_id == STORAGE_TILE && !m_HasStorage ) {
			if (Editor::StoragesPlaced < Editor::BoxesCount
				&& m_TileId == FLOOR_TILE || m_TileId == BOX_TILE) {
				Editor::StoragesPlaced++;
				if (m_HasBox) set_sprite("box-gold");
				else set_sprite("editor-storage");
				m_HasStorage = true;
				m_TileId = FLOOR_TILE;
			}
		}
		else if (tile_id == PLAYER_TILE && !Editor::PlayerPlaced) {
			if (m_TileId == FLOOR_TILE && !m_HasBox) {
				m_HasPlayer = true;
				Editor::PlayerPlaced = true;
				Editor::PlayerTile->m_TilePos = m_TilePos;
				Editor::PlayerTile->set_position(TILES_START + get_size() * (vec2f)m_TilePos);
				Editor::PlayerTile->appear();
			}
		}
		select(m_IsSelected);
	}
}

Tool::Tool(uint8_t id, const std::string& sprite)
	: UISelectBox(sprite, "editor-tool-selection"), m_TileId(id)
{
}
