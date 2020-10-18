#include "AssetsManager.h"
#include "Logger.h"

bool AssetsManager::load_texture(const std::string& file_path, const std::string& asset_id, bool smooth)
{
    sf::Texture* texture = new sf::Texture();
    if (texture->loadFromFile(file_path)) {
        if (smooth)
            texture->setSmooth(true);
        m_Textures[asset_id] = texture;
        LOG_INFO("AssetsManager: loaded texture '", '\b' + asset_id, "\b'");
        return true;
    }
    else return false;
}

sf::Texture* AssetsManager::get_texture(const std::string& asset_id)
{
    return m_Textures.at(asset_id);
}

AssetsManager::AssetsManager()
{
}

AssetsManager::~AssetsManager()
{
    for (auto& t : m_Textures)
        delete t.second;
    m_Textures.clear();
}
