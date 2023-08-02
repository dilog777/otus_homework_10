#pragma once

#include "Command.h"



class CommandEndBlock : public Command
{
public:
	void execute(CommandMachine *machine) const override;
};
