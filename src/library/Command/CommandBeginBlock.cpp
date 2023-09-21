#include "CommandBeginBlock.h"

#include "CommandMachine.h"



CommandBeginBlock::CommandBeginBlock()
	: Command { Type::BeginBlock }
{
}



void CommandBeginBlock::execute(CommandMachine *machine) const
{
	machine->beginBlock();
}
