#include <iostream>
#include <stdexcept>
#include <fstream>
#include "./argparser/argparser.cpp"

int main (int argc, char* argv[]) {

    if (argc == 1) {
        std::cerr << "Pass at least a path to the database binary.";
        return 1;
    }

    ArgParser arguments = ArgParser(argc, argv);

    std::cout << "filepath: " << arguments.db << std::endl; 

    return 0;
}   