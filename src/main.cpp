#include <iostream>
#include <stdexcept>
#include <fstream>
#include <optional>
#include "lib/dot-commands/dot-commands.hpp"
#include "lib/argparser/argparser.hpp"
#include "lib/utils/strings.cpp"


int main (int argc, const char* argv[]) {

    if (argc == 1) {
        std::cerr << "Pass at least a path to the database binary.";
        return 1;
    }

    ArgParser arguments = ArgParser(argc, argv);

    // open db file
    std::string databaseFilepath = arguments.shortFlags["f"];
    std::ifstream databaseFile(databaseFilepath, std::ios::binary);

    if (!databaseFile) {
        std::cerr << "Failed to open the database file" << std::endl;
        return 1;
    }

    // get dot command
    std::optional<std::string> dotCommand = getDotCommand(arguments.positional);

    if (dotCommand.value() == ".dbinfo") {
        dbinfo(databaseFile);
    } else if (dotCommand.value() == ".tables") {
        tables(databaseFile);
    }

    return 0;
}   