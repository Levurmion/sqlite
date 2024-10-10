#ifndef RECORDS_SERIAL
#define RECORDS_SERIAL

#include <iostream>

enum RecordSerial {
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

RecordSerial determineColumnSerial(uint64_t varint);

#endif