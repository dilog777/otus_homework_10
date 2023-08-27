#pragma once

class CommandMachine;


class Command
{
public:
	virtual ~Command() = default;

	virtual void execute(CommandMachine *machine) const = 0;
};
