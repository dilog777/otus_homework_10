#pragma once

#include "GlobalMacroses.h"
#include "Logger.h"



class FileLogger : public Logger
{
	DISABLE_COPY(FileLogger)

public:
	FileLogger();
	~FileLogger() override;

	void log(time_t time, const std::string &str) override;

	void finishWork() const;

private:
	class Impl;
	Impl *_impl;
};
