#pragma once
#include <vector>
#include <string>
#include <sstream>

class utils {
public:
	static std::vector<std::string> str_split(std::string str, char split_char) {
		std::stringstream ss(str);
		std::string segment;
		std::vector<std::string> segments;
		while (std::getline(ss, segment, split_char))
			segments.emplace_back(segment);
		return segments;
	}
};
