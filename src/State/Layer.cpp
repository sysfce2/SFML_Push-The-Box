#include "Layer.h"

void Layer::hide(bool freeze)
{
	for (auto& entity : m_LayerEntities)
		entity->vanish(freeze);
}

void Layer::show()
{
	for (auto& entity : m_LayerEntities)
		entity->appear(false);
}
