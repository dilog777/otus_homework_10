#include "BlockLogger.h"

#include <chrono>
#include <iostream>
#include <fstream>



void BlockLogger::startBlock()
{
	auto now = std::chrono::system_clock::now();
	_startBlock = std::chrono::system_clock::to_time_t(now);
}



void BlockLogger::log(const std::string& str)
{
	std::cout << str << std::endl;

	auto fileName = "bulk" + std::to_string(_startBlock) + ".log";
	std::ofstream out;
	//out.open(fileName);
	//if (out.is_open())
	//{
	//	out << str << std::endl;
	//}
	//out.close();
}
