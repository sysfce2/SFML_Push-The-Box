#include "Box.h"
#include "Game/TileMap.h"

void Box::update(const float& dt)
{
	update_movements(dt);
	if (m_CheckForStorage && m_VelocityPx.is_zero()) {
		m_CheckForStorage = false;
		bool found = false;

		for (const auto& storage : m_TileMap->m_StoragePositions) {
			if (storage == m_TilePos) {
				if (!m_IsOnStorage) {
					m_TileMap->m_StoragesFilled++;
					set_sprite("box-gold");
				}
				found = true;
				break;
			}
		}
		if (m_IsOnStorage && !found) {
			m_TileMap->m_StoragesFilled--;
			set_sprite("box");
		}

		m_IsOnStorage = found;
	}
}

Box::Box(vec2f place_pos, vec2u tile_pos, TileMap* t_ptr) 
	: m_TilePos(tile_pos), m_TileMap(t_ptr)
{
	set_position_px(place_pos);
	set_sprite("box");
}
