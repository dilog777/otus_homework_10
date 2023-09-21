#include "CommandEndBlock.h"

#include "CommandMachine.h"



CommandEndBlock::CommandEndBlock()
	: Command { Type::EndBlock }
{
}



void CommandEndBlock::execute(CommandMachine *machine) const
{
	machine->endBlock();
}
