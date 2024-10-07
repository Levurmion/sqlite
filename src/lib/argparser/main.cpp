#include <iostream>
#include "argparser.cpp"

int main (int argc, char* argv[]) {

    ArgParser arguments = ArgParser(argc, argv);

    std::cout << "Positional Arguments: " << std::endl;
    for (std::string positionalArg : arguments.positional) {
        std::cout << positionalArg << " ";
    }
    std::cout << std::endl;
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