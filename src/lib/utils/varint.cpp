#include <iostream>
#include <fstream>
#include <cassert>
#include <memory>
#include <algorithm>
#include "math.cpp"
#include "bits.cpp"


struct VarintByte {
    unsigned char contBit;
    unsigned char payload;

    VarintByte() {};

    VarintByte(unsigned char byte) {
        contBit = (byte >> 7) & 0x01;
        payload = byte & 0x7f;
    }

    // Copy constructor
    VarintByte(const VarintByte& other) {
        contBit = other.contBit;
        payload = other.payload;
    }

    /**
     * Returns the byte representation of a `VarintByte`.
     */
    unsigned char getByte() const {
        return (contBit << 7) | payload;
    }

    /**
     * Returns whether this `VarintByte` expects a continuation byte.
     */
    bool shouldContinue() const {
        return (0x01 & contBit) > 0;
    }
};


class Varint {

    private:
        std::vector<VarintByte> varintBytes;
        unsigned char finalVarintByte = 0;

        /**
         * Computes the number of bytes required to encode a `uint64_t` as a `varint`.
         */
        int getVarintByteSize (uint64_t number) {
            int leadingZeros = countLeadingZeros(number);
            if (leadingZeros < 8) {
                // will require the full 9 `VarintBytes`
                return 9;
            } else {
                int occupiedBits = 64 - leadingZeros;
                return ceiling(occupiedBits, 7);
            }
        };
    
    public:
        typedef std::vector<Varint> VarintVector;

        Varint() {
            varintBytes.reserve(8);
        };

        /**
         * Construct `Varint` from a byte buffer stream.
         */
        Varint(std::vector<unsigned char>& buffer) {
            varintBytes.reserve(8);
            for (unsigned char byte : buffer) {
                if (expectsMoreBytes()) {
                    this->addByte(byte);
                } else {
                    break;
                }
            }
        };

        /**
         * Construct `Varint` from a `uint64_t` integer.
         */
        Varint(uint64_t num) {
            int varintByteSize = getVarintByteSize(num);
            varintBytes.reserve(varintByteSize > 8 ? 8 : varintByteSize);

            if (varintByteSize >= 9) {
                // all but the last 8 LSBs will be discarded
                finalVarintByte = static_cast<unsigned char>(num);
                varintByteSize -= 1;
                num = num >> 8;
            }

            for (int i = 0; i < varintByteSize; i++) {
                // extract the 8 LSBs
                unsigned char byte = static_cast<unsigned char>(num);
                if (i == 0) {
                    if (finalVarintByte > 0) {
                        byte = byte | 0x80;
                    } else {
                        byte = byte & 0x7f;
                    }
                } else {
                    byte = byte | 0x80;
                }
                VarintByte varintByte = VarintByte(byte);
                varintBytes.push_back(varintByte);
                num = num >> 7;
            }
            
            // reverse varintBytes
            std::reverse(varintBytes.begin(), varintBytes.end());
        };

        Varint(const Varint& other) {
            varintBytes = other.varintBytes;
            finalVarintByte = other.finalVarintByte;
        };

        /**
         * Checks if this `Varint` expects additional bytes.
         */
        bool expectsMoreBytes () {
            if (varintBytes.size() > 0) {
                return varintBytes.back().shouldContinue() && finalVarintByte == 0;
            } else {
                return true;
            }
        }

        /**
         * Add an extra byte to the varint.
         */
        void addByte (unsigned char byte) {
            if (expectsMoreBytes()) {
                if (varintBytes.size() >= 8) {
                    finalVarintByte = byte;
                } else {
                    varintBytes.push_back(VarintByte(byte));
                }
            }
        };

        /**
         * Return the encoded varint value as a `uint64_t`.
         */
        std::optional<uint64_t> getInt () {
            if (expectsMoreBytes()) {
                return std::nullopt;
            }

            uint64_t varint = 0;
            for (VarintByte varintByte : varintBytes) {
                varint = varint << 7;
                varint = varint | varintByte.payload;
            }
            
            if (finalVarintByte > 0) {
                varint = varint << 8;
                varint = varint | static_cast<uint64_t>(finalVarintByte);
            }

            return varint;
        }

        /**
         * Return the `Varint` as a vector of bytes.
         */
        std::optional<std::vector<unsigned char>> getBytes () {
            if (expectsMoreBytes()) {
                return std::nullopt;
            }

            int numVarintBytes = varintBytes.size() + (finalVarintByte > 0 ? 1 : 0);
            std::vector<unsigned char> varintByteStream;
            varintByteStream.resize(numVarintBytes);

            int i = 0;
            for (VarintByte varintByte: varintBytes) {
                varintByteStream[i] = varintByte.getByte();
                i++;
            }

            if (finalVarintByte > 0) {
                varintByteStream[8] = finalVarintByte;
            }

            return varintByteStream;
        }

        /**
         * Decodes a collection of static Huffman-encoded varint values from a byte buffer
         * stream.
         */
        static std::optional<VarintVector> decodeVarintFromBuffer (unsigned char* buffer, uint size) {
            std::vector<Varint> varints;
            Varint currVarint = Varint();
            for (int i = 0; i < size; i++) {
                unsigned char byte = buffer[i];
                if (!currVarint.expectsMoreBytes()) {
                    varints.push_back(currVarint);
                    currVarint = Varint();
                }
                currVarint.addByte(byte);
            }
            
            if (!currVarint.expectsMoreBytes()) {
                // the last constructed varint is complete
                varints.push_back(currVarint);
                return varints;
            } else {
                // the last constructed varint is not complete
                return std::nullopt;
            }
        }
};