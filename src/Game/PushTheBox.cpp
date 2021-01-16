#include "PushTheBox.h"
#include "MainMenu.h"
#include "Core/Logger.h"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

bool PushTheBox::on_init()
{
	bool success = true;
	std::ifstream resources("resources");
	std::string line;
	if (resources.is_open()) {
		while (getline(resources, line))
			if (line.size() > 0 && line[0] != '#') {
				using namespace std;
				line.erase(std::remove(line.begin(), line.end(), ','), line.end());
				stringstream ss(line);
				istream_iterator<string> begin(ss);
				istream_iterator<string> end;
				vector<string> args(begin, end);
				if (args[0] == "FONT") 
					success |= AssetsManager::get().load_font(args[1], args[2]);
				else 
					success |= AssetsManager::get().load_texture(args[0], args[1], stoi(args[2]));
			}
	}
	else {
		m_InitErrorMessage = "Failed to load game resources list";
		return false;
	}
	resources.close();

	if (!success) {
		m_InitErrorMessage = "Failed to load game resources";
		return false;
	}

	StatesManager::get().create_active_state(new MainMenu());
	return true;
}

bool PushTheBox::on_update(const float& dt)
{
	return true;
}
