#include "record-header.hpp"
#include "../utils/varint.cpp"
#include <iostream>
#include <fstream>
#include <iomanip>

RecordHeader::RecordHeader(std::ifstream& file, int offset) {
    // set to cell offset
    file.seekg(offset);
    std::vector<u_char> buffer(9);

    // decode cellSize
    file.read(reinterpret_cast<char*>(buffer.data()), 9);
    Varint cellSizeVarint = Varint(buffer);
    if (cellSizeVarint.getInt().has_value()) {
        cellSize = cellSizeVarint.getInt().value();
    } else {
        throw std::runtime_error("Cannot decode cell size.");
    }

    // decode rowId
    file.seekg(offset + cellSizeVarint.getByteCount());
    file.read(reinterpret_cast<char*>(buffer.data()), 9);
    Varint rowIdVarint = Varint(buffer);
    if (rowIdVarint.getInt().has_value()) {
        rowId = rowIdVarint.getInt().value();
    } else {
        throw std::runtime_error("Cannot decode row id.");
    }

    // save cell header size
    cellHeaderSize = cellSizeVarint.getByteCount() + rowIdVarint.getByteCount();

    // decode headerSize
    file.seekg(
        offset + 
        cellSizeVarint.getByteCount() + 
        rowIdVarint.getByteCount()
    );
    file.read(reinterpret_cast<char*>(buffer.data()), 9);
    Varint headerSizeVarint = Varint(buffer);
    if (headerSizeVarint.getInt().has_value()) {
        recordHeaderSize = headerSizeVarint.getInt().value();
    } else {
        throw std::runtime_error("Cannot decode header size.");
    }

    // decode all the headers
    buffer.resize(recordHeaderSize - headerSizeVarint.getByteCount());
    file.seekg(
        offset + 
        cellSizeVarint.getByteCount() + 
        rowIdVarint.getByteCount() + 
        headerSizeVarint.getByteCount()
    );
    file.read(reinterpret_cast<char*>(buffer.data()), recordHeaderSize - headerSizeVarint.getByteCount());
    std::optional<Varint::VarintVector> result = Varint::decodeVarintFromBuffer(buffer.data(), buffer.size());

    if (result.has_value()) {
        Varint::VarintVector headerVarints = result.value();
        std::vector<RecordSerial> columnSerials(headerVarints.size());
        
        for (int i = 0; i < headerVarints.size(); i++) {
            Varint headerVarint = headerVarints[i];
            if (headerVarint.getInt().has_value()) {
                columnSerials[i] = determineColumnSerial(headerVarint.getInt().value());
            }
        }

        columns = columnSerials;
        numColumns = columnSerials.size();
    } else {
        throw std::runtime_error("Cannot decode cell headers.");
    }
}