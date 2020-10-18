#include "AssetsManager.h"

bool AssetsManager::load_texture(std::string path, std::string name_id)
{
    sf::Texture* texture = new sf::Texture();
    if (texture->loadFromFile(path)) {
        textures[name_id] = texture;
        return true;
    }
    else return false;
}

sf::Texture* AssetsManager::get_texture(std::string name_id)
{
    return textures.at(name_id);
}

AssetsManager::AssetsManager()
{
}

AssetsManager::~AssetsManager()
{
    for (auto& t : textures)
        delete t.second;
    textures.clear();
}
