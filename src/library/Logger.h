#pragma once

#include <string>



class Logger
{
public:
	virtual ~Logger() = default;
	
	virtual void log(time_t time, const std::string &str) = 0;
};
