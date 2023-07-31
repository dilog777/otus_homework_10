#pragma once

#include "Logger.h"



class BlockLogger : public Logger
{
public:
	void startBlock();

	void log(const std::string &str) override;

private:
	time_t _startBlock { 0 };
};
