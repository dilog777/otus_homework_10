#include "Logger.h"

#include <chrono>
#include <iostream>
#include <fstream>



void Logger::beginBlock()
{
	auto now = std::chrono::system_clock::now();
	_beginBlock = std::chrono::system_clock::to_time_t(now);
}



void Logger::log(const std::string& str)
{
	std::cout << str << std::endl;

	auto fileName = "bulk" + std::to_string(_beginBlock) + ".log";
	std::ofstream out;
	//out.open(fileName);
	//if (out.is_open())
	//{
	//	out << str << std::endl;
	//}
	//out.close();
}
