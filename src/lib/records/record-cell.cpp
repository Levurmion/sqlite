#include "record-cell.hpp"
#include "record-header.hpp"
#include "record-serial.hpp"
#include "../types/columns.cpp"
#include "../utils/bits.cpp"
#include "../utils/vectors.cpp"
#include <iostream>
#include <fstream>


void RecordCell::parseColumn(RecordSerial serial, u_int start) {
    switch(serial.type) {
        case SerialType::INT_8: {
            columns.push_back(new Uint8(static_cast<uint8_t>(buffer[start])));
            break;
        }
        case SerialType::INT_16: {
            uint16_t value = concatenateBytes<uint16_t>(buffer, start, 2);
            columns.push_back(new Uint16(value));
        }
            break;
        case SerialType::INT_24: {
            uint32_t value = concatenateBytes<uint32_t>(buffer, start, 3);
            columns.push_back(new Uint24(value));
        }
            break;
        case SerialType::INT_32: {
            uint32_t value = concatenateBytes<uint32_t>(buffer, start, 4);
            columns.push_back(new Uint32(value));
        }
            break;
        case SerialType::INT_48: {
            uint64_t value = concatenateBytes<uint64_t>(buffer, start, 6);
            columns.push_back(new Uint48(value));
        }
            break;
        case SerialType::INT_64: {
            uint64_t value = concatenateBytes<uint64_t>(buffer, start, 8);
            columns.push_back(new Uint64(value));
        }
            break;
        case SerialType::FALSE: {
            columns.push_back(new Boolean(false));
            break;
        }
        case SerialType::TRUE: {
            columns.push_back(new Boolean(true));
            break;
        }
        case SerialType::BLOB: {
            columns.push_back(new Blob(slice(buffer, start, start + serial.size)));
            break;
        }
        case SerialType::STRING: {
            columns.push_back(new String(slice(buffer, start, start + serial.size)));
            break;
        }
        default: {
            return;
        }
    }
}


RecordCell::RecordCell(RecordHeader& header, std::ifstream& file, int offset) {
    // read in the entire cell into buffer
    buffer.resize(header.cellSize + 2);
    file.seekg(offset);
    file.read(reinterpret_cast<char*>(buffer.data()), header.cellSize + 2);

    // determine the byte start offset in the buffer
    uint colStart = header.cellHeaderSize + header.recordHeaderSize;

    // parse columns
    for (int i = 0; i < header.numColumns; i++) {
        auto columnSerial = header.columns[i];
        parseColumn(columnSerial, colStart);
        colStart += columnSerial.size;
    }
};


RecordCell::~RecordCell() {
    // destroy ColumnValue objects
    for (auto column: columns) {
        delete column;
    }
}


