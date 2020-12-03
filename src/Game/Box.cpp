#include "Box.h"
#include "TileMap.h"

void Box::update(const float& dt)
{
	if (m_CheckForTarget) {
		m_CheckForTarget = false;
		bool found = false;

		for (const auto& target : TileMap::s_Targets) {
			if (target == m_TilePos) {
				if (!m_IsOnTarget)
					TileMap::s_BoxesOnTargets++;
				set_sprite("box-gold");
				found = true;
				break;
			}
		}
		
		if (m_IsOnTarget && !found) {
			TileMap::s_BoxesOnTargets--;
			set_sprite("box");
		}

		m_IsOnTarget = found;
	}
}

Box::Box(const vec2f& place_pos, vec2u tile_pos) : m_TilePos(tile_pos)
{
	set_sprite("box");
	set_position_px(place_pos);
	set_scale({ 1.5f, 1.5f });
}
