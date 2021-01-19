#include "PushTheBox.h"
#include "MainMenu.h"
#include "Core/Logger.h"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

bool PushTheBox::on_init()
{
	bool success = true;
	ifstream resources("resources");
	if (resources.is_open()) {
		string line;
		while (getline(resources, line))
			if (line.size() > 0 && line[0] != '#') {

				line.erase(remove(line.begin(), line.end(), ','), line.end());
				stringstream ss(line);
				istream_iterator<string> begin(ss);
				istream_iterator<string> end;
				vector<string> args(begin, end);

				if (args[0] == "FONT") 
					success |= AssetsManager::get().load_font(args[1], args[2]);
				else 
					success |= AssetsManager::get().load_texture(args[0], args[1], stoi(args[2]));
			}
		resources.close();
	}
	else {
		m_InitErrorMessage = "Failed to load game resources list";
		return false;
	}

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
