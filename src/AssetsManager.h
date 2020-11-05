#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

class AssetsManager
{
public:
	friend class Application;
	static bool load_texture(const std::string& file_name, const std::string& asset_id, bool smooth = false);
	static sf::Texture* get_texture(const std::string& asset_id);

private:
	static void free_memory();
	static std::unordered_map<std::string, sf::Texture*> m_Textures;
};