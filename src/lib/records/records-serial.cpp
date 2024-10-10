#include "records-serial.hpp"
#include <iostream>

RecordSerial determineColumnSerial(uint64_t serial) {
    switch (serial) {
        case 0:
            return RecordSerial(SerialType::SQLITE_NULL, 0);
        case 1:
            return RecordSerial(SerialType::INT_8, 1);
        case 2:
            return RecordSerial(SerialType::INT_16, 2);
        case 3:
            return RecordSerial(SerialType::INT_24, 3);
        case 4:
            return RecordSerial(SerialType::INT_32, 4);
        case 5:
            return RecordSerial(SerialType::INT_48, 6);
        case 6:
            return RecordSerial(SerialType::INT_64, 8);
        case 7:
            return RecordSerial(SerialType::FLOAT_64, 8);
        case 8:
            return RecordSerial(SerialType::FALSE, 0);
        case 9:
            return RecordSerial(SerialType::TRUE, 0);
        case 10:
            return RecordSerial(SerialType::VARIABLE_1, 0);
        case 11:
            return RecordSerial(SerialType::VARIABLE_2, 0);
        default:
            uint remainder = serial % 2;
            bool isEven = remainder == 0;
            if (isEven) {
                return RecordSerial(SerialType::BLOB, (serial-12)/2);
            } else {
                return RecordSerial(SerialType::STRING, (serial-13)/2);
            }
    }
}