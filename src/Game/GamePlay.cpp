#pragma once
#include "GamePlay.h"
#include "TileMap.h"
#include "Player.h"
#include "Core/Logger.h"

using KB = sf::Keyboard;

void GamePlay::update(const float& dt)
{	
	if (KB::isKeyPressed(KB::Escape))
		destroy_state();
	
	vec2f player_pos = m_Player->get_position();

	if (player_pos.x - m_CameraOffset.x > 1.f - m_CameraBorderDistance) {
		m_CameraOffset.x = player_pos.x - 1.f + m_CameraBorderDistance;
	}
	else if (player_pos.x - m_CameraOffset.x < m_CameraBorderDistance) {
		m_CameraOffset.x = player_pos.x - m_CameraBorderDistance;
	}

	if (player_pos.y - m_CameraOffset.y > 1.f - m_CameraBorderDistance) {
		m_CameraOffset.y = player_pos.y - 1.f + m_CameraBorderDistance;
	}
	else if (player_pos.y - m_CameraOffset.y < m_CameraBorderDistance) {
		m_CameraOffset.y = player_pos.y - m_CameraBorderDistance;
	}

	if (m_TileMap->s_Targets.size() == m_TileMap->s_BoxesOnTargets) {
		destroy_state();
	}
}

GamePlay::GamePlay(const std::string& level_path)
{
	m_Background = new UIElement("gameplay-background", { 1.f, 1.f });
	m_TileMap = new TileMap();
	make_entity(m_Background);

	if (m_TileMap->load_level(level_path)) {
		for (auto tile : m_TileMap->m_Tiles)
			make_entity(tile);

		for (auto box : m_TileMap->m_Boxes)
			make_entity(box);

		m_Player = m_TileMap->m_Player;
		make_entity(m_Player);
	}
	else {
		LOG_ERROR("Can't find game level:", level_path);
		destroy_state();
	}
}