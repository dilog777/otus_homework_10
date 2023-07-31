#pragma once

#include <string>

class Logger
{
public:
	virtual ~Logger() = default;

	virtual void log(const std::string &str) = 0;
};
