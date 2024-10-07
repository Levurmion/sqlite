#include <iostream>
#include <stdexcept>
#include <fstream>
#include "../lib/argparser/argparser.cpp"
#include "../lib/utils/strings.cpp"

using namespace std;

int main (int argc, char* argv[]) {

    if (argc == 1) {
        std::cerr << "Pass at least a path to the database binary.";
        return 1;
    }

    ArgParser arguments = ArgParser(argc, argv);

    for (string arg : arguments.positional) {
        std::cout << arg << " ";
    }
    std::cout << std::endl;


    return 0;
}   