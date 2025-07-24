#pragma once
#include <string>

class CommandParser {
public:
    Command parse(std::string cmdString);
};
