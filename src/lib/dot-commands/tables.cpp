#include "dot-commands.hpp"
#include "../utils/numbers.cpp"
#include "../utils/varint.cpp"
#include "../records/record-header.hpp"
#include <iostream>
#include <fstream>
#include <stdio.h>


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
        std::cout << "cell size: " << recordHeader.cellSize << " ";
        std::cout << "row id: " << recordHeader.rowId << " ";
        std::cout << "header size: " << recordHeader.headerSize << std::endl;

        int col = 0;
        for (RecordSerial column : recordHeader.columns) {
            std::cout << "column: " << col << " type: " << column.type << " size: " << column.size << std::endl;
            col++;
        }
    }

    delete[] cellOffsets;
};