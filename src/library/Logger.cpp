#include "Logger.h"

#include <fstream>

#include "ConsoleLogger.h"



Logger::Logger()
	: _consoleLogger { new ConsoleLogger }
{
}



void Logger::log(time_t timeStamp, const std::string &str) const
{
	_consoleLogger->log(str);
	
	auto fileName = "bulk" + std::to_string(timeStamp) + ".log";
	std::ofstream out;
	out.open(fileName);
	if (out.is_open())
	{
		out << str << std::endl;
	}
	out.close();
}
