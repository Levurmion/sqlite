#ifndef COLUMN_TYPES
#define COLUMN_TYPES

#include <iostream>
#include <string>
#include <variant>
#include <any>

struct ColumnValue {

    virtual std::string toString() const = 0;
    virtual ~ColumnValue() {};
};

struct Null: ColumnValue {
    std::monostate getValue() const {
        return std::monostate{};
    }
    std::string toString() const override {
        return "NULL";
    }
};

struct Uint8: ColumnValue {
    uint8_t value;

    explicit Uint8(uint8_t value): value(value) {};
    uint8_t getValue() const {
        return value;
    }
    std::string toString() const override {
        return std::to_string(value);
    }
};

struct Uint16: ColumnValue {
    uint16_t value;

    explicit Uint16(uint16_t value): value(value) {};
    uint16_t getValue() const {
        return value;
    }
    std::string toString() const override {
        return std::to_string(value);
    }
};

struct Uint24: ColumnValue {
    uint32_t value;

    explicit Uint24(uint32_t value) {
        this->value = value & 0x00ffffff;
    };
    uint32_t getValue() const {
        return value;
    }
    std::string toString() const override {
        return std::to_string(value);
    }
};

struct Uint32: ColumnValue {
    uint32_t value;

    explicit Uint32(uint32_t value): value(value) {};
    uint32_t getValue() const {
        return value;
    }
    std::string toString() const override {
        return std::to_string(value);
    }
};

struct Uint48: ColumnValue {
    uint64_t value;

    explicit Uint48(uint64_t value) {
        this->value = value & 0x00ffffffffffffff;
    };
    uint64_t getValue() const {
        return value;
    }
    std::string toString() const override {
        return std::to_string(value);
    }
};

struct Uint64: ColumnValue {
    uint64_t value;
    
    explicit Uint64(uint64_t value): value(value) {};
    uint64_t getValue() const {
        return value;
    }
    std::string toString() const override {
        return std::to_string(value);
    }
};

struct Float64: ColumnValue {
    double value;

    explicit Float64(double value): value(value) {};
    double getValue() const {
        return value;
    }
    std::string toString() const override {
        return std::to_string(value);
    }
};

struct Blob: ColumnValue {
    std::vector<unsigned char> value;

    explicit Blob(std::vector<unsigned char> bytes): value(bytes) {};
    std::vector<unsigned char> getValue() const {
        return value;
    }
    std::string toString() const override {
        return std::string(value.begin(), value.end());
    }
};

struct String: ColumnValue {
    std::string value;

    explicit String(std::vector<unsigned char> bytes) {
        std::string stringValue(bytes.begin(), bytes.end());
        value = stringValue;
    };
    std::string getValue() const {
        return value;
    }
    std::string toString() const override {
        return value;
    }
};

struct Boolean: ColumnValue {
    bool value;

    explicit Boolean(bool value): value(value) {};
    bool getValue() const {
        return value;
    }
    std::string toString() const override {
        return value ? "TRUE" : "FALSE";
    }
};

#endif