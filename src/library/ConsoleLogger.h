#pragma once

#include "Logger.h"



class ConsoleLogger : public Logger
{
public:
	ConsoleLogger();
	~ConsoleLogger() override;

	void log(time_t time, const std::string &str) override;

private:
	class Impl;
	Impl *_impl;
};
