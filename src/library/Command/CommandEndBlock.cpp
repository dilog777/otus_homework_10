#include "CommandEndBlock.h"

#include "CommandMachine.h"



void CommandEndBlock::execute(CommandMachine *machine) const
{
	machine->endBlock();
}
