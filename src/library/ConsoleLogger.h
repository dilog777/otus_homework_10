#pragma once

#include <string>



class ConsoleLogger
{
public:
	ConsoleLogger();
	~ConsoleLogger();
	
	void log(const std::string &str);

private:
	class Impl;
	Impl *_impl;
};
