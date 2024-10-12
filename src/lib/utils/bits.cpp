#include <iostream>

/**
 * Count the number of leading zeros.
 */
inline uint countLeadingZeros(uint64_t number) {
    if (number == 0) {
        return 64;
    }
    uint zeros = 0;
    for (int i = 63; i >= 0; --i) {
        // number masked against left shifts of 0x00000001 will only be larger than 0
        // if the bit at the shifted position in number is 1
        if ((number & (static_cast<uint64_t>(1) << i)) > 0) {
            break;
        }
        zeros += 1;
    }
    return zeros;
}