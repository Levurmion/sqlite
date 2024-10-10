#include "dot-commands.hpp"
#include "../utils/numbers.cpp"
#include <iostream>
#include <fstream>
#include <stdio.h>


void tables (std::ifstream& databaseFile) {
    char uintBuffer[2];
    
    // the first page has the database file header
    databaseFile.seekg(HEADER_SIZE + 3);
    databaseFile.read(uintBuffer, 2);
    u_int cellCount = bufferToUint16<unsigned char>(uintBuffer);

    // record all cell offsets
    u_int* cellOffsets = new u_int[cellCount];

    for (int i = 0; i < cellCount; i++) {
        // cell pointer array starts right after btree page header
        databaseFile.seekg(HEADER_SIZE + BTREE_HEADER_LEAF_SIZE + (i * 2));
        databaseFile.read(uintBuffer, 2);
        cellOffsets[i] = bufferToUint16<unsigned char>(uintBuffer);
    }

    for (int i = 0; i < cellCount; i++) {
        u_int currCellOffset = cellOffsets[i];
        uint64_t cellSize = getVarintFromIfstream(databaseFile, currCellOffset);

        // load in the entire cell into memory
        unsigned char* cellBuffer = new unsigned char[cellSize];
        databaseFile.seekg(currCellOffset);
        databaseFile.read(reinterpret_cast<char*>(cellBuffer), cellSize);

        // read row id
        uint rowIdOffset = getVarintSize(cellSize);
        uint64_t rowId = decodeVarint(cellBuffer, rowIdOffset);
        std::cout << rowId << std::endl;
        delete[] cellBuffer;
    }

    delete[] cellOffsets;
};