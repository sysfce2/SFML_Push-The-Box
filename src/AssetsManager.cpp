#include "AssetsManager.h"

bool AssetsManager::load_texture(std::string path, std::string asset_id, bool smooth)
{
    sf::Texture* texture = new sf::Texture();
    if (texture->loadFromFile(path)) {
        if (smooth)
            texture->setSmooth(true);
        textures[asset_id] = texture;
        return true;
    }
    else return false;
}

sf::Texture* AssetsManager::get_texture(std::string asset_id)
{
    return textures.at(asset_id);
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
