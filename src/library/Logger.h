#pragma once

#include <string>



class Logger
{
public:
	void beginBlock();

	void log(const std::string &str);

private:
	time_t _beginBlock { 0 };
};
