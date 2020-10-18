#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

class AssetsManager
{
private:
	std::unordered_map<std::string, sf::Texture*> textures;
public:
	bool load_texture(std::string path, std::string name_id);
	sf::Texture* get_texture(std::string name_id);

	AssetsManager();
	virtual ~AssetsManager();
};