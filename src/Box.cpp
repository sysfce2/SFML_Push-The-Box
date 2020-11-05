#include "Box.h"

void Box::update(const float& dt)
{
	if (m_CheckForTarget) {
		m_CheckForTarget = false;
		bool found = false;

		for (const auto& target : *m_TargetsPtr) {
			if (target == m_TilePos) {
				if (!m_IsOnTarget)
					(*m_BoxesOnTargetsPtr)++;
				set_sprite("box-gold");
				found = true;
				break;
			}
		}
		
		if (m_IsOnTarget && !found) {
			(*m_BoxesOnTargetsPtr)--;
			set_sprite("box");
		}

		m_IsOnTarget = found;
	}
}

Box::Box(const vec2f& place_pos, vec2u tile_pos, std::vector<vec2u>* tp, uint16_t* btp)
	: m_TilePos(tile_pos), m_TargetsPtr(tp), m_BoxesOnTargetsPtr(btp)
{
	set_sprite("box");
	set_position_px(place_pos);
	set_scale(vec2f(1.5f, 1.5f));
}

Box::~Box()
{
}
