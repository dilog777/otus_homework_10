#include "CommandText.h"

#include "CommandMachine.h"



CommandText::CommandText(const std::string &name)
	: Command { Type::Text }
	, _name { name }
{
}



void CommandText::execute(CommandMachine *machine) const
{
	machine->textCommand(_name);
}
