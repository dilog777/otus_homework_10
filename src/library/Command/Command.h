#pragma once

class CommandMachine;


class Command
{
public:
	enum class Type
	{
		Undef,
		BeginBlock,
		EndBlock,
		Text
	};

	Command(Type type);
	Type type() const;

	virtual ~Command() = default;

	virtual void execute(CommandMachine *machine) const = 0;

private:
	Type _type { Type::Undef };
};
