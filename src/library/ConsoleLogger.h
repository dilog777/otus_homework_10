#pragma once

#include "GlobalMacroses.h"
#include "Logger.h"



class ConsoleLogger : public Logger
{
	DISABLE_COPY(ConsoleLogger)

public:
	ConsoleLogger();
	~ConsoleLogger() override;

	void log(time_t time, const std::string &str) override;

	void finishWork() const;

private:
	class Impl;
	Impl *_impl;
};
