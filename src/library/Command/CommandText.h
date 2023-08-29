#pragma once

#include <string>

#include "Command.h"



class CommandText : public Command
{
public:
	CommandText(const std::string &name);

	void execute(CommandMachine *machine) const override;

private:
	std::string _name;
};
