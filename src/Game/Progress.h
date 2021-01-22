#pragma once
#include "Core/Vector2.h"
#include <vector>

#define LEVELS_COUNT 16

struct LevelInfo
{
	bool completed = false;
	u32 time = 0;
	u32 moves = 0;
};

using Levels = std::vector<LevelInfo>;

class GameProgress
{
public:
	friend class PushTheBox;
	inline static GameProgress& get() {
		if (s_Instance == nullptr)
			s_Instance = new GameProgress();
		return *s_Instance;
	}

	LevelInfo* get_level_info(u16 number);
	void load();
	void save();

	GameProgress();
private:
	std::string get_checksum(Levels* lvls);

	static GameProgress* s_Instance;
	Levels m_Levels;

};