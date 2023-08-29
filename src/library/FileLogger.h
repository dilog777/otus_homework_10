#pragma once

#include "Logger.h"



class FileLogger : public Logger
{
public:
	FileLogger();
	~FileLogger() override;
	
	void log(time_t time, const std::string &str) override;

private:
	class Impl;
	Impl *_impl;
};
