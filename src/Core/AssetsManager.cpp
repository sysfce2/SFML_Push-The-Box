#include "Core/AssetsManager.h"
#include "Core/Logger.h"

std::unordered_map<std::string, sf::Texture*> AssetsManager::m_Textures;
std::unordered_map<std::string, sf::Font*> AssetsManager::m_Fonts;

bool AssetsManager::load_texture(const std::string& file_name, const std::string& asset_id, bool smooth)
{
    sf::Texture* texture = new sf::Texture();
    if (texture->loadFromFile("assets/" + file_name)) {
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
    if (m_Textures.find(asset_id) == m_Textures.end()) {
        LOG_ERROR("AssetsManager: Could not find texture of id '", '\b' + asset_id, "\b'");
        return nullptr;
    }
        
    return m_Textures.at(asset_id);
}

bool AssetsManager::load_font(const std::string& file_name, const std::string& asset_id)
{
    sf::Font* font = new sf::Font();
    if (font->loadFromFile("assets/" + file_name)) {
        m_Fonts[asset_id] = font;
        LOG_INFO("AssetsManager: loaded font '", '\b' + asset_id, "\b'");
        return true;
    }
    else return false;
}

sf::Font* AssetsManager::get_font(const std::string& asset_id)
{
    if (m_Fonts.find(asset_id) == m_Fonts.end()) {
        LOG_ERROR("AssetsManager: Could not find font of id '", '\b' + asset_id, "\b'");
        return nullptr;
    }
    return m_Fonts.at(asset_id);
}

void AssetsManager::free_memory()
{
    for (auto& t : m_Textures)
        delete t.second;
    m_Textures.clear();
}
