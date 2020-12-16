#pragma once
#include "GamePlay.h"
#include "TileMap.h"
#include "Player.h"
#include "Core/Logger.h"
#include "State/StatesManager.h"

using KB = sf::Keyboard;
constexpr float A_RATIO = 9.f / 16.f;
constexpr float CTRL_BTNS_SPACING = 0.02f;
const vec2f BTN_SCALE{ 2.8f, 2.8f };

void GamePlay::update(const float& dt)
{	
	vec2f player_pos = m_Player->get_position();
	vec2f player_size = m_Player->get_size();
	vec2f camera_offset = player_pos - m_Camera;

	// Prawa strona
	if (camera_offset.x + player_size.x > m_fovWidth - m_CameraBorderDistance * A_RATIO)
		m_Camera.x = player_pos.x + player_size.x - m_fovWidth + m_CameraBorderDistance * A_RATIO;
	// Lewa strona
	else if (player_pos.x - m_Camera.x < m_CameraBorderDistance * A_RATIO)
		m_Camera.x = player_pos.x - m_CameraBorderDistance * A_RATIO;
	// Górna strona
	if (camera_offset.y + player_size.y > 1.f - m_CameraBorderDistance)
		m_Camera.y = player_pos.y + player_size.y - 1.f + m_CameraBorderDistance;
	// Dolna strona
	else if (camera_offset.y < m_CameraBorderDistance)
		m_Camera.y = player_pos.y - m_CameraBorderDistance;

	if (m_PlayerMoves > m_Moves) {
		m_Moves = m_PlayerMoves;
		m_MovesText->set_text(L"Ruchy: " + std::to_wstring(m_Moves));
		m_MovesText->center_x();
	}

	if (KB::isKeyPressed(KB::Up) || m_MoveUp->is_pressed())
		PlayerControl::go_up = true;
	else PlayerControl::go_up = false;

	if (KB::isKeyPressed(KB::Down) || m_MoveDown->is_pressed())
		PlayerControl::go_down = true;
	else PlayerControl::go_down = false;

	if (KB::isKeyPressed(KB::Right) || m_MoveRight->is_pressed())
		PlayerControl::go_right = true;
	else PlayerControl::go_right = false;

	if (KB::isKeyPressed(KB::Left) || m_MoveLeft->is_pressed())
		PlayerControl::go_left = true;
	else PlayerControl::go_left = false;

	if (m_TileMap->s_Targets.size() == m_TileMap->s_BoxesOnTargets) {
		destroy_state();
	}

	if (m_Restart->was_pressed()) {
		destroy_state();
		StatesManager::get().create_active_state(new GamePlay(m_LevelPath, m_LevelNameStr));
	}

	if (m_Exit->was_pressed())
		destroy_state();
}

GamePlay::GamePlay(const std::string& level_path, const std::wstring& name)
	: m_LevelPath(level_path), m_LevelNameStr(name)
{
	m_TileMap = new TileMap();
	PlayerControl::go_up = false;
	PlayerControl::go_down = false;
	PlayerControl::go_right = false;
	PlayerControl::go_left = false;

	if (m_TileMap->load_level(m_LevelPath)) {
		// Initialize UI elements
		m_Background = new UIElement("gameplay-background", { 1.f, 1.f });
		m_Menu = new UIElement("gameplay-menu", { 1.f, 1.f });
		m_LevelName = new UIText(m_LevelNameStr, "joystix", 26);
		m_MovesText = new UIText("Ruchy: 0", "joystix", 24);
		m_UndoButton = new UIButton("COFNIJ", BTN_SCALE, 22);
		m_MoveUp = new UIButton("", BTN_SCALE);
		m_MoveDown = new UIButton("", BTN_SCALE);
		m_MoveRight = new UIButton("", BTN_SCALE);
		m_MoveLeft = new UIButton("", BTN_SCALE);
		m_Restart = new UIButton(L"RESTART", { 2.f, 2.f }, 26);
		m_Exit = new UIButton(L"WYJD", { 2.f, 2.f }, 26);

		// Construct background
		make_entity(m_Background);

		// Construct tilemap
		for (auto tile : m_TileMap->m_Tiles)
			make_entity(tile);

		for (auto box : m_TileMap->m_Boxes)
			make_entity(box);

		m_Player = m_TileMap->m_Player;
		m_Player->m_Moves = &m_PlayerMoves;
		make_entity(m_Player);

		// Construct UI menu
		m_fovWidth = 1.f - m_Menu->get_size().x;
		m_Menu->set_position({ m_fovWidth, 0.f });
		m_LevelName->attach_position(m_Menu).set_position({ 0.f, 0.05f }).center_x();
		m_MovesText->attach_position(m_Menu).set_position({ 0.f, 0.13f }).center_x();
		m_UndoButton->assign_button_sprite("btn-3x1", "btn-3x1-pressed");
		m_UndoButton->attach_position(m_Menu).set_position({ 0.f, 0.2f }).center_x();

		UIElement* arrow_up = new UIElement("arrow_up", BTN_SCALE);
		UIElement* arrow_down = new UIElement("arrow_down", BTN_SCALE);
		UIElement* arrow_right = new UIElement("arrow_right", BTN_SCALE);
		UIElement* arrow_left = new UIElement("arrow_left", BTN_SCALE);

		m_MoveUp->assign_button_sprite("btn-1x1", "btn-1x1-pressed");
		m_MoveUp->attach_position(m_Menu).set_position({ 0.f, 0.4f }).center_x();
		m_MoveUp->set_symbol(arrow_up);

		float down_y = m_MoveUp->get_position().y + m_MoveUp->get_size().y + CTRL_BTNS_SPACING * 3.f;
		float length_y = (m_MoveUp->get_size().y * 2.f + CTRL_BTNS_SPACING * 3.f) / 2.f;
		float side_y = m_MoveUp->get_position().y + length_y - m_MoveUp->get_size().y / 2.f;
		float left_x = m_MoveUp->get_position().x - m_MoveUp->get_size().x - CTRL_BTNS_SPACING * A_RATIO;
		float right_x = m_MoveUp->get_position().x + m_MoveUp->get_size().x + CTRL_BTNS_SPACING * A_RATIO;

		m_MoveDown->assign_button_sprite("btn-1x1", "btn-1x1-pressed");
		m_MoveDown->attach_position(m_Menu).set_position({ 0.f, down_y }).center_x();
		m_MoveDown->set_symbol(arrow_down);

		m_MoveRight->assign_button_sprite("btn-1x1", "btn-1x1-pressed");
		m_MoveRight->attach_position(m_Menu).set_position({ right_x, side_y });
		m_MoveRight->set_symbol(arrow_right);

		m_MoveLeft->assign_button_sprite("btn-1x1", "btn-1x1-pressed");
		m_MoveLeft->attach_position(m_Menu).set_position({ left_x, side_y });
		m_MoveLeft->set_symbol(arrow_left);

		m_Restart->attach_position(m_Menu).set_position({ 0.f, 0.75f }).center_x();
		m_Exit->attach_position(m_Menu).set_position({ 0.f, 0.85f }).center_x();

		make_entity(m_Menu);
		make_entity(m_LevelName);
		make_entity(m_MovesText);
		make_entity(m_UndoButton);
		make_entity(m_MoveUp);
		make_entity(m_MoveDown);
		make_entity(m_MoveRight);
		make_entity(m_MoveLeft);
		make_entity(m_Restart);
		make_entity(m_Exit);
	}
	else {
		LOG_ERROR("Can't find game level:", level_path);
		destroy_state();
	}
}