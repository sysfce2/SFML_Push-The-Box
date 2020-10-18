#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

class AssetsManager
{
public:
	bool load_texture(std::string path, std::string asset_id, bool smooth = false);
	sf::Texture* get_texture(std::string asset_id);

	AssetsManager();
	virtual ~AssetsManager();
private:
	std::unordered_map<std::string, sf::Texture*> textures;
};