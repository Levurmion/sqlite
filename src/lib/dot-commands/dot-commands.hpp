#ifndef DOT_COMMAND
#define DOT_COMMAND

#include <iostream>
#include <optional>

std::optional<std::string> getDotCommand (const std::vector<std::string>& positionalArgs);

#endif