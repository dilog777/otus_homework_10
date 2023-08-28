#pragma once

#include <string>
#include <memory>

class ConsoleLogger;



class Logger
{
public:
	Logger();
	
	void log(time_t timeStamp, const std::string &str) const;

private:
	std::shared_ptr<ConsoleLogger> _consoleLogger;
};
