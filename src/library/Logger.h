#pragma once

#include <string>



class Logger
{
public:
	void log(time_t timeStamp, const std::string &str) const;
};
