#pragma once

#include "Command.h"



class CommandBeginBlock : public Command
{
public:
	void execute(CommandMachine *machine) const override;
};
