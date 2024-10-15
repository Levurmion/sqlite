#ifndef RECORD_CELL
#define RECORD_CELL

#include "../types/columns.cpp"
#include "record-header.hpp"
#include "record-serial.hpp"
#include <iostream>
#include <fstream>
#include <any>

class RecordCell {

    private:
        std::vector<u_char> buffer;

        void parseColumn(RecordSerial recordSerial, u_int start);

    public:
        RecordHeader header;
        std::vector<ColumnValue*> columns;

        RecordCell(RecordHeader& header, std::ifstream& file, int offset);
        ~RecordCell();
};

#endif