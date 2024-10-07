#include <iostream>
#include <stdexcept>
#include <fstream>
#include "lib/argparser/argparser.hpp"
#include "lib/utils/strings.hpp"

using namespace std;

int main (int argc, const char* argv[]) {

    if (argc == 1) {
        std::cerr << "Pass at least a path to the database binary.";
        return 1;
    }

    ArgParser arguments = ArgParser(argc, argv);

    std::cout << "Positional Arguments: " << std::endl;
    for (std::string positionalArg : arguments.positional) {
        std::cout << positionalArg << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Short Flags: " << std::endl;
    for (const auto& [key, value] : arguments.shortFlags) {
        std::cout << key << ": " << value << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Long Flags: " << std::endl;
    for (const auto& [key, value] : arguments.longFlags) {
        std::cout << key << ": " << value << std::endl;
    }
    std::cout << std::endl;


    return 0;
}   