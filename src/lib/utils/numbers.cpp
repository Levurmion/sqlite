#include <iostream>
#include <fstream>

template <typename Target>
u_int bufferToUint16 (const char buffer[]) {
    return 
        (static_cast<u_int>(static_cast<Target>(buffer[0])) << 8) | 
        static_cast<u_int>(static_cast<Target>(buffer[1]))
    ;
}

// ============= VARINTS =============

struct VarintByte {
    unsigned contBit: 1;
    unsigned payload: 7;

    VarintByte(char byte) {
        contBit = (byte >> 7) & 0x01;
        payload = byte & 0x7f;
    }
};

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


inline uint ceiling(uint a, uint b) {
    return (a + b - 1)/b;
}


/**
 * Computes the number of bytes required to encode a `uint64_t` as a `varint`.
 */
inline uint getVarintSize (uint64_t number) {
    uint leadingZeros = countLeadingZeros(number);
    if (leadingZeros < 8) {
        // will require the full 9 `VarintBytes`
        return 9;
    } else {
        uint occupiedBits = 64 - leadingZeros;
        return ceiling(occupiedBits, 7);
    }
};


/**
 * Decodes a `varint` from a starting byte in a `char` buffer.
 */
inline uint64_t decodeVarint(const unsigned char buffer[], uint16_t offset) {
    const uint MAX_LEN = 8;
    VarintByte* varintBytes[8] = {};
    uint finalVarintByte = 0;

    for (int i = 0; i < MAX_LEN; i++) {
        unsigned char byte = buffer[offset + i];
        VarintByte varintByte = VarintByte(byte);
        varintBytes[i] = &varintByte;
        if (varintByte.contBit == 0x00) {
            break;
        }
    }

    if (varintBytes[7] != nullptr && varintBytes[7]->contBit == 0x01) {
        finalVarintByte = buffer[offset + 8];
    }

    // construct the resulting uint64_t
    uint64_t varint = 0;
    for (VarintByte* pVarintByte : varintBytes) {
        if (pVarintByte == nullptr) {
            break;
        }
        // std::cout << std::bitset<64>(varint) << std::endl;
        VarintByte varintByte = *pVarintByte;
        varint = varint << 7;                        // shift existing bits left by 7 bits
        varint = varint | varintByte.payload;        // add in the next payload
    }

    // add the finalVarintByte if exists
    if (finalVarintByte > 0x00) {
        varint = varint << 8;
        varint = varint | finalVarintByte;
    }

    return varint;
}


/**
 * Extracts a `varint` from a `std::ifstream` at a specific byte offset.
 */
inline uint64_t getVarintFromIfstream (std::ifstream& file, uint offset) {
    // pull 9 bytes directly into memory since this is the max length of a `varint`
    unsigned char buffer[9];
    file.seekg(offset);
    file.read(reinterpret_cast<char*>(buffer), 9);
    return decodeVarint(buffer, 0);
}