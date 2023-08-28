#pragma once

#include <string>



class FileLogger
{
public:
	FileLogger();
	~FileLogger();
	
	void log(time_t time, const std::string &str);

private:
	class Impl;
	Impl *_impl;
};
