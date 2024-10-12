#include <gtest/gtest.h>
#include <string>
#include <stdexcept>
#include "varint.cpp"

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

TEST(DecodeVarintFromBufferTest, VarintDecodedProperly) {
    unsigned char varintBuffer[] = {0b10000001, 0b00000001, 0b00000111};   // only first 2 bytes = 129
    std::optional<Varint::VarintVector> result = Varint::decodeVarintFromBuffer(varintBuffer, 3);
    ASSERT_NE(result, std::nullopt);
    Varint::VarintVector varintVector = result.value();
    EXPECT_EQ(varintVector[0].getInt(), 129);
}

TEST(DecodeVarintFromBufferTest, LongVarintDecodedProperly) {
    unsigned char varintBuffer[] = {
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
    std::optional<Varint::VarintVector> result = Varint::decodeVarintFromBuffer(varintBuffer, 9);
    ASSERT_NE(result, std::nullopt);
    Varint::VarintVector varintVector = result.value();
    EXPECT_EQ(varintVector[0].getInt(), 145249953336295809);
}

TEST(DecodeVarintFromBufferTest, MultipleVarintsCanBeDecoded) {
    unsigned char varintBuffer[] = {
        // first varint: 128
        0b10000001, 
        0b00000000, 
        // second varint: 130
        0b10000001, 
        0b00000010,
        // third varint: 135
        0b10000001, 
        0b00000111,
    };
    std::optional<Varint::VarintVector> result = Varint::decodeVarintFromBuffer(varintBuffer, 6);
    ASSERT_NE(result, std::nullopt);
    Varint::VarintVector varints = result.value();
    EXPECT_EQ(varints[0].getInt(), 128);
    EXPECT_EQ(varints[1].getInt(), 130);
    EXPECT_EQ(varints[2].getInt(), 135);
}

TEST(DecodeVarintFromBufferTest, BadBufferReturnsNullopt) {
    unsigned char varintBuffer[] = {
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
    };
    std::optional<Varint::VarintVector> result = Varint::decodeVarintFromBuffer(varintBuffer, 10);
    ASSERT_EQ(result, std::nullopt);
}

TEST(DecodeVarintFromBufferTest, VarintConstructedFromBuffer) {
    std::vector<unsigned char> varintBuffer = {0b10000001, 0b00000001, 0b00000111};   // only first 2 bytes = 129
    Varint varint = Varint(varintBuffer);
    EXPECT_EQ(varint.getInt(), 129);
}

TEST(EncodeVarintFromIntegerTest, SmallVarintConstructedFromBuffer) {
    Varint varint = Varint(129);
    std::optional<std::vector<unsigned char>> result = varint.getBytes();
    ASSERT_NE(result, std::nullopt);

    std::vector<unsigned char> bytes = result.value();
    EXPECT_EQ(bytes.size(), 2);

    EXPECT_EQ(bytes[0], 0b10000001);
    EXPECT_EQ(bytes[1], 0b00000001);
}

TEST(EncodeVarintFromIntegerTest, LargeVarintConstructedFromBuffer) {
    Varint varint = Varint(145249953336295809);
    std::optional<std::vector<unsigned char>> result = varint.getBytes();
    ASSERT_NE(result, std::nullopt);

    std::vector<unsigned char> bytes = result.value();
    EXPECT_EQ(bytes.size(), 9);

    std::vector<unsigned char> expectedBytes = {
        0b10000001, 
        0b10000001, 
        0b10000001, 
        0b10000001,
        0b10000001,
        0b10000001,
        0b10000001,
        0b10000001,
        0b10000001,
    };
    for (int i = 0; i < 9; i++) {
        EXPECT_EQ(bytes[i], expectedBytes[i]);
    }
}