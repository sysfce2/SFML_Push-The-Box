#pragma once
#include "StatePlaying.h"
#include "TileMap.h"
#include "Player.h"
#include "Logger.h"

using KB = sf::Keyboard;

void StatePlaying::update(const float& dt)
{	
	if (KB::isKeyPressed(KB::Escape))
		destroy_state();

	if (m_Player->get_position().x - m_CameraOffset.x > 1.f - m_CameraBorderDistance) {
		m_CameraOffset.x = m_Player->get_position().x - 1.f + m_CameraBorderDistance;
	}
	else if (m_Player->get_position().x - m_CameraOffset.x < m_CameraBorderDistance) {
		m_CameraOffset.x = m_Player->get_position().x - m_CameraBorderDistance;
	}

	if (m_Player->get_position().y - m_CameraOffset.y > 1.f - m_CameraBorderDistance * 16 / 9) {
		m_CameraOffset.y = m_Player->get_position().y - 1.f + m_CameraBorderDistance * 16 / 9;
	}
	else if (m_Player->get_position().y - m_CameraOffset.y < m_CameraBorderDistance * 16 / 9) {
		m_CameraOffset.y = m_Player->get_position().y - m_CameraBorderDistance * 16 / 9;
	}
}

StatePlaying::StatePlaying()
{
	m_TileMap = new TileMap();
	m_TileMap->load_level("test-level.txt");

	for (auto tile : m_TileMap->m_Tiles)
		make_entity(tile);

	for (auto box : m_TileMap->m_Boxes)
		make_entity(box);

	m_Player = m_TileMap->m_Player;
	make_entity(m_Player);
}

StatePlaying::~StatePlaying()
{
}