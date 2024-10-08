#include "dot-commands.hpp"
#include "../utils/strings.hpp"

#include <iostream>
#include <optional>

std::optional<std::string> getDotCommand(const std::vector<std::string>& positionalArgs) {
    for (std::string arg: positionalArgs) {
        if (startsWith(arg, ".")) {
            return arg;
        }
    }
    return std::nullopt;
}