#pragma once
#include <map>
#include "Entity/Entity.h"

#define MAX_LAYERS 32
#define LAYER_1  0x00000001
#define LAYER_2  0x00000002
#define LAYER_3  0x00000004
#define LAYER_4  0x00000008
#define LAYER_5  0x00000010
#define LAYER_6  0x00000020
#define LAYER_7  0x00000040
#define LAYER_8  0x00000080
#define LAYER_9  0x00000100
#define LAYER_10 0x00000200
#define LAYER_11 0x00000400
#define LAYER_12 0x00000800
#define LAYER_13 0x00001000
#define LAYER_14 0x00002000
#define LAYER_15 0x00004000
#define LAYER_16 0x00008000
#define LAYER_17 0x00010000
#define LAYER_18 0x00020000
#define LAYER_19 0x00040000
#define LAYER_20 0x00080000
#define LAYER_21 0x00100000
#define LAYER_22 0x00200000
#define LAYER_23 0x00400000
#define LAYER_24 0x00800000
#define LAYER_25 0x01000000
#define LAYER_26 0x02000000
#define LAYER_27 0x04000000
#define LAYER_28 0x08000000
#define LAYER_29 0x10000000
#define LAYER_30 0x20000000
#define LAYER_31 0x40000000
#define LAYER_32 0x80000000

class Layer
{
public:
	friend class State;
	void hide(bool freeze = false);
	void show();
	Layer() = default;
	virtual ~Layer() = default;
private:
	std::vector<Entity*> m_LayerEntities;
};