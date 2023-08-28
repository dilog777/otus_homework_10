#include "Logger.h"

#include "ConsoleLogger.h"
#include "FileLogger.h"



Logger::Logger()
	: _consoleLogger { new ConsoleLogger }
	, _fileLogger { new FileLogger }
{
}



void Logger::log(time_t time, const std::string &str) const
{
	_consoleLogger->log(time, str);
	_fileLogger->log(time, str);
}
