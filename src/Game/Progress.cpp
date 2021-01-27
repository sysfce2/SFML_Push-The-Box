#include "Progress.h"
#include "Core/Logger.h"
#include "Utils/sha256.h"

#include <fstream>

GameProgress* GameProgress::s_Instance = nullptr;

LevelInfo* GameProgress::get_level_info(u16 number)
{
	if (number <= m_Levels.size() && number > 0)
		return const_cast<LevelInfo*>(&m_Levels.at(number - 1));
	else return nullptr;
}

void GameProgress::load()
{
	std::ifstream file("game.progress");
	Levels levels_read; levels_read.reserve(LEVELS_COUNT);
	if (file.is_open()) {
		char checksum[65] = { 0 };
		file.read(checksum, 64);
		for (u16 i = 0; i < LEVELS_COUNT; i++) {
			if (file.eof()) {
				LOG_ERROR("Game progress file was corrupted");
				save(); break;
			}
			LevelInfo info;
			file.read(reinterpret_cast<char*>(&info), sizeof(LevelInfo));
			levels_read.emplace_back(info);
		}

		if (levels_read.size() == LEVELS_COUNT) {
			std::string s_checksum = std::string(checksum);
			if (s_checksum == get_checksum(&levels_read)) {
				LOG_INFO("Game progress file successfully loaded");
				m_Levels = levels_read;
			}
			else {
				LOG_ERROR("Game progress file was corrupted");
				save();
			}
		}
		file.close();
	}
	else save();
}

void GameProgress::save()
{
	char checksum[65];
	std::string s_checksum = get_checksum(&m_Levels).c_str();
	strcpy_s(checksum, s_checksum.c_str());
	std::ofstream file("game.progress");
	file.write(checksum, 64);
	for (auto& lvl : m_Levels)
		file.write(reinterpret_cast<char*>(&lvl), sizeof(LevelInfo));
	file.close();
}

GameProgress::GameProgress()
{
	m_Levels.reserve(LEVELS_COUNT);
	for (u16 i = 0; i < LEVELS_COUNT; i++)
		m_Levels.emplace_back(LevelInfo());
}

std::string GameProgress::get_checksum(Levels* lvls)
{
	auto get_secret = [&]() -> std::string {
		constexpr char letters[] = "abcdefghijklmnopqrstuvwxyz";
		constexpr u16 size = 16;
		srand(420);
		std::string secret;
		for (u16 i = 0; i < size; i++)
			secret += letters[rand() % (sizeof(letters) - 1)];
		return secret;
	};
	std::string to_checksum = get_secret();
	for (auto& lvl : *lvls)
		to_checksum += std::to_string(lvl.time) + std::to_string(lvl.moves);
	return sha256(to_checksum);
}
