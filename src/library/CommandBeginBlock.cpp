#include "CommandBeginBlock.h"

#include "CommandMachine.h"



void CommandBeginBlock::execute(CommandMachine *machine) const
{
	machine->beginBlock();
}
