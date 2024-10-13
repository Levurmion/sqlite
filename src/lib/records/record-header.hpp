#ifndef RECORD_HEADER
#define RECORD_HEADER

#include "record-serial.hpp"
#include <iostream>
#include <fstream>

class RecordHeader {

    private:
        std::vector<u_char> buffer;

    public:
        uint64_t cellSize;
        uint64_t headerSize;
        uint64_t rowId;
        std::vector<RecordSerial> columns;

        /**
         * Read the header for a record from a binary file stream at a given
         * file byte offset.
         */
        RecordHeader(std::ifstream& file, int offset);
};

#endif