#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

class AssetsManager
{
public:
	friend class Application;
	bool load_texture(const std::string& file_name, const std::string& asset_id, bool smooth = false);
	bool load_font(const std::string& file_name, const std::string& asset_id);
	sf::Texture* get_texture(const std::string& asset_id);
	sf::Font* get_font(const std::string& asset_id);

	inline static AssetsManager& get() {
		if (s_Instance == nullptr)
			s_Instance = new AssetsManager();
		return *s_Instance;
	}

private:
	void free_memory();
	static AssetsManager* s_Instance;
	static std::unordered_map<std::string, sf::Texture*> m_Textures;
	static std::unordered_map<std::string, sf::Font*> m_Fonts;
};