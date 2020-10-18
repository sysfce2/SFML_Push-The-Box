#pragma once
#include "Logger.h"

HANDLE Logger::m_ConsoleHandle;

void Logger::display_log(int log_type, std::string msg)
{
	uint16_t print_color = 7;
	switch (log_type) {
	case 1:
		std::cout << "[INFO] ";
		print_color = _INFO_COLOR;
		break;
	case 2:
		std::cout << "[WARN] ";
		print_color = _WARN_COLOR;
		break;
	case 3:
		std::cout << "[ERROR] ";
		print_color = _ERROR_COLOR;
		break;
	default:
		std::cout << "[LOG] ";
		print_color = _LOG_COLOR;
		break;
	}

	SetConsoleTextAttribute(Logger::m_ConsoleHandle, print_color);
	std::cout << msg << std::endl;
	SetConsoleTextAttribute(Logger::m_ConsoleHandle, 7);
}

void Logger::init()
{
	Logger::m_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}

std::string Logger::to_string()
{
	return std::string();
}