#pragma once
#include <string>
#include "Command.h"

class CommandParser {
public:
    Command parse(std::string cmdString);
};