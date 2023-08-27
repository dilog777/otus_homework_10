#pragma once

#include <string>



class CommandMachine
{
public:
	virtual ~CommandMachine() = default;

	virtual void beginBlock() = 0;
	virtual void endBlock() = 0;
	virtual void textCommand(const std::string &text) = 0;
};
