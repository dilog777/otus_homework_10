#pragma once

#include <string>
#include <memory>

class ConsoleLogger;
class FileLogger;



class Logger
{
public:
	Logger();
	
	void log(time_t time, const std::string &str) const;

private:
	std::shared_ptr<ConsoleLogger> _consoleLogger;
	std::shared_ptr<FileLogger> _fileLogger;
};
