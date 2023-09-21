#pragma once

#include "Command.h"



class CommandEndBlock : public Command
{
public:
	CommandEndBlock();

	void execute(CommandMachine *machine) const override;
};
