#include "Logger.h"

#include <iostream>
#include <fstream>



void Logger::log(time_t timeStamp, const std::string &str) const
{
	std::cout << str << std::endl;

	auto fileName = "bulk" + std::to_string(timeStamp) + ".log";
	std::ofstream out;
	out.open(fileName);
	if (out.is_open())
	{
		out << str << std::endl;
	}
	out.close();
}
