#ifndef RECORD_HEADER
#define RECORD_HEADER

#include "record-serial.hpp"
#include <iostream>
#include <fstream>

class RecordHeader {

    public:
        uint64_t cellSize;
        uint64_t cellHeaderSize;
        uint64_t recordHeaderSize;
        uint64_t rowId;
        std::vector<RecordSerial> columns;
        uint numColumns;

        RecordHeader() {};

        /**
         * Read the header for a record from a binary file stream at a given
         * cell byte offset on the page.
         */
        RecordHeader(std::ifstream& file, int offset);
};

#endif