#pragma once

#include "Command.h"



class CommandBeginBlock : public Command
{
public:
	CommandBeginBlock();
	
	void execute(CommandMachine *machine) const override;
};
