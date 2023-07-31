#pragma once

#include <string>



class Command
{
public:
	Command(const std::string &name);

	const std::string &name() const;

private:
	std::string _name;
};
