#include "dbinfo.hpp"
#include <iostream>
#include <fstream>

void dbinfo (std::ifstream& databaseFile) {

    // set file pointer to 16th byte
    databaseFile.seekg(16);

    // read into a 2-byte buffer
    char buffer[2];
    databaseFile.read(buffer, 2);

    // big-endian: most sig byte in buffer[0], followed by buffer[1]
    unsigned int pageSize = (static_cast<unsigned int>(buffer[0]) << 8) | static_cast<unsigned int>(buffer[1]);

    std::cout << "Page Size: " << pageSize << std::endl;
}