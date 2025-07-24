#include "CommandParser.h"
#include <sstream>
#include <vector>
#include <algorithm>


Command CommandParser::parse(std::string cmdString) {
    Command cmd;
    cmdString.erase(0, cmdString.find_first_not_of(" \t\n\r")); // Removing Whitespace
    cmdString.erase(cmdString.find_last_not_of(" \t\n\r") + 1);

    std::istringsteam iss(cmdString);
    std::string word;

    if(!(iss >> word)) { // Empty input case
        cmd.type = "";
        return cmd;
    }
    cmd.type = word;

    while (iss >> word) {
        cmd.args.push_back(word);
    }

    std::transform(cmd.type.begin(), cmd.type.end(), cmd.type.begin(), ::tolower);
    return cmd;
}