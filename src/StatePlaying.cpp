#pragma once
#include "StatePlaying.h"

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
	m_Player = new Player();
	make_entity(m_Player);
	auto wall1 = make_entity(new Wall());
	wall1->set_position(vec2f(.6f, .6f));
	wall1->set_scale(vec2f(1.5f, 1.5f));
}

StatePlaying::~StatePlaying()
{
}