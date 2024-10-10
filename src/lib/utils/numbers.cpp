#include <iostream>

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
 * Decodes a `varint` from a starting byte in a `char` buffer.
 */
inline uint64_t decodeVarint(const unsigned char buffer[], uint16_t startByte) {
    const uint MAX_LEN = 8;
    VarintByte* varintBytes[8] = {};
    uint finalVarintByte = 0;

    for (int i = 0; i < MAX_LEN; i++) {
        unsigned char byte = buffer[startByte + i];
        VarintByte varintByte = VarintByte(byte);
        varintBytes[i] = &varintByte;
        if (varintByte.contBit == 0x00) {
            break;
        }
    }

    if (varintBytes[7] != nullptr && varintBytes[7]->contBit == 0x01) {
        finalVarintByte = buffer[startByte + 8];
    }

    // construct the resulting uint64_t
    uint64_t varint = 0;
    for (VarintByte* pVarintByte : varintBytes) {
        if (pVarintByte == nullptr) {
            break;
        }
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