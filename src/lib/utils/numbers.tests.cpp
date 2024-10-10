#include <gtest/gtest.h>
#include <string>
#include <stdexcept>
#include "numbers.cpp"

using namespace std;

TEST(VarintByteTest, VarintByteInstantiatedCorrectly) {
    char byteA = 0b10000111;
    VarintByte varintByteA = VarintByte(byteA);
    EXPECT_EQ(varintByteA.contBit, 0x01);
    EXPECT_EQ(varintByteA.payload, 0x07);

    char byteB = 0b00000111;
    VarintByte varintByteB = VarintByte(byteB);
    EXPECT_EQ(varintByteB.contBit, 0x00);
    EXPECT_EQ(varintByteB.payload, 0x07);
}

TEST(DecodeVarintTest, VarintDecodedProperly) {
    unsigned char varint[] = {0b10000001, 0b00000001, 0b00000111};   // only first 2 bytes = 129
    uint64_t result = decodeVarint(varint, 0);
    EXPECT_EQ(result, 129);
}

TEST(DecodeVarintTest, LongVarintDecodedProperly) {
    unsigned char varint[] = {
        0b10000001, 
        0b10000001, 
        0b10000001, 
        0b10000001,
        0b10000001,
        0b10000001,
        0b10000001,
        0b10000001,
        0b10000001,
        0b10000001,
    };  // only first 9 bytes = 145,249,953,336,295,809
    uint64_t result = decodeVarint(varint, 0);
    EXPECT_EQ(result, 145249953336295809);
}