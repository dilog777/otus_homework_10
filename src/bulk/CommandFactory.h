#pragma once

#include <memory>
#include <string>

class Command;


class CommandFactory
{
public:
	static std::shared_ptr<Command> makeCommand(const std::string &str);
};
