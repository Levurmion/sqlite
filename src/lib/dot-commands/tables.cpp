#include "dot-commands.hpp"
#include "../types/columns.cpp"
#include "../utils/numbers.cpp"
#include "../utils/varint.cpp"
#include "../records/record-header.hpp"
#include "../records/record-cell.hpp"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <variant>


void tables (std::ifstream& databaseFile) {
    char uintBuffer[2];
    
    // the first page has the database file header
    databaseFile.seekg(HEADER_SIZE + 3);
    databaseFile.read(uintBuffer, 2);
    u_int cellCount = bufferToUint16<u_char>(uintBuffer);

    // record all cell offsets
    u_int* cellOffsets = new u_int[cellCount];

    for (int i = 0; i < cellCount; i++) {
        // cell pointer array starts right after btree page header
        databaseFile.seekg(HEADER_SIZE + BTREE_HEADER_LEAF_SIZE + (i * 2));
        databaseFile.read(uintBuffer, 2);
        cellOffsets[i] = bufferToUint16<u_char>(uintBuffer);
    }

    for (int i = 0; i < cellCount; i++) {
        u_int cellOffset = cellOffsets[i];
        RecordHeader recordHeader = RecordHeader(databaseFile, cellOffset);
        RecordCell recordCell = RecordCell(recordHeader, databaseFile, cellOffset);

        // table_name is column 3
        std::cout << recordCell.columns[2]->toString() << " ";
    }

    std::cout << std::endl;
    delete[] cellOffsets;
};