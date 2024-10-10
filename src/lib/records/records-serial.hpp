#ifndef RECORDS_SERIAL
#define RECORDS_SERIAL

#include <iostream>

enum SerialType {
    SQLITE_NULL,
    INT_8,
    INT_16,
    INT_24,
    INT_32,
    INT_48,
    INT_64,
    FLOAT_64,
    FALSE,
    TRUE,
    VARIABLE_1,
    VARIABLE_2,
    BLOB,
    STRING
};


struct RecordSerial {
    SerialType type;
    uint size;

    RecordSerial(SerialType type, uint size): type(type), size(size) {};
};

/**
 * Given a serial code extracted from a record header, return its `SerialType`
 * and `size` of the column in bytes.
 */
RecordSerial determineColumnSerial(uint64_t serial);

#endif