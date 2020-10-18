#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

class AssetsManager
{
public:
	bool load_texture(const std::string& file_path, const std::string& asset_id, bool smooth = false);
	sf::Texture* get_texture(const std::string& asset_id);

	AssetsManager();
	virtual ~AssetsManager();
private:
	std::unordered_map<std::string, sf::Texture*> m_Textures;
};