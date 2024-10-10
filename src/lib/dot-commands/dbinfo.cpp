#include "dot-commands.hpp"
#include "../utils/numbers.hpp"
#include <iostream>
#include <fstream>

void dbinfo (std::ifstream& databaseFile) {
    // no conversions needed as std::cout will interpret chars as ASCII
    char header[16];
    databaseFile.read(header, 16);
    std::cout << header << std::endl;

    // set file pointer to 16th byte
    databaseFile.seekg(16);

    // read into a 2-byte buffer
    char buffer[2];
    databaseFile.read(buffer, 2);

    // big-endian: most sig byte in buffer[0], followed by buffer[1]
    // static_cast to unsigned int will turn 0000 0001 to 0000 0000 0000 0001
    // shift left by 8 bits turns this into 0000 0001 0000 0000
    unsigned int pageSize = bufferToUint16<unsigned char>(buffer);

    std::cout << "database page size:" << "\t" << pageSize << std::endl;

    // B-tree page header is an 8 or 12-byte section at offset 0
    // the first page includes the 100-byte databae file header so we will offset
    // this by 100. The cell count for a page is at offset 3 from the start of
    // the B-tree page.
    databaseFile.seekg(HEADER_SIZE + 3);
    databaseFile.read(buffer, 2);

    unsigned int cellCount = bufferToUint16<unsigned char>(buffer);

    std::cout << "number of tables:" << "\t" << cellCount << std::endl;
}