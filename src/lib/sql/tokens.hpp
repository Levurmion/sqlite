#ifndef SQL_TOKENS
#define SQL_TOKENS

#include <iostream>
#include <string>
#include <regex>

enum class SQLTokenType {
    Clause,
    Identifier,
    Delimiter,
    AggregateFunction,
    Wildcard,
    Operator,
    Epsilon,
    Terminator,
};

// Overload operator<< for SQLTokenType
inline std::ostream& operator<<(std::ostream& os, const SQLTokenType& tokenType) {
    switch (tokenType) {
        case SQLTokenType::Clause: return os << "Clause";
        case SQLTokenType::Identifier: return os << "Identifier";
        case SQLTokenType::Delimiter: return os << "Delimiter";
        case SQLTokenType::AggregateFunction: return os << "AggregateFunction";
        case SQLTokenType::Wildcard: return os << "Wildcard";
        case SQLTokenType::Operator: return os << "Operator";
        case SQLTokenType::Epsilon: return os << "Epsilon";
        case SQLTokenType::Terminator: return os << "Terminator";
        default: return os << "UnknownTokenType";
    }
}

struct Token {
    SQLTokenType type;
    std::string value;

    bool operator==(const Token& other) const {
        return other.type == this->type && other.value == this->value;
    }
};

const std::vector<std::tuple<SQLTokenType, std::regex>> TOKENS = {
    {SQLTokenType::Clause, std::regex(R"(\bSELECT|FROM|WHERE|CREATE|INSERT|UPDATE|DELETE|JOIN|AND|OR|AS\b)", std::regex_constants::icase)},
    {SQLTokenType::AggregateFunction, std::regex(R"(\bCOUNT|SUM|AVG|MIN|MAX\b)", std::regex_constants::icase)},
    {SQLTokenType::Delimiter, std::regex(R"([\(\),;.])")},
    {SQLTokenType::Wildcard, std::regex(R"(\*)")},
    {SQLTokenType::Operator, std::regex(R"(=|!=|<=|>=|<|>)")},
    {SQLTokenType::Identifier, std::regex(R"([A-Za-z_][A-Za-z0-9_]*)")},
};


// token instances
namespace SQLTokens {
    
    // -- CLAUSES

    const Token SELECT = Token{SQLTokenType::Clause, "SELECT"};
    const Token CREATE = Token{SQLTokenType::Clause, "CREATE"};
    const Token INSERT = Token{SQLTokenType::Clause, "INSERT"};
    const Token UPDATE = Token{SQLTokenType::Clause, "UPDATE"};
    const Token DELETE = Token{SQLTokenType::Clause, "DELETE"};
    const Token WHERE = Token{SQLTokenType::Clause, "WHERE"};
    const Token FROM = Token{SQLTokenType::Clause, "FROM"};
    const Token JOIN = Token{SQLTokenType::Clause, "JOIN"};
    const Token AND = Token{SQLTokenType::Clause, "AND"};
    const Token OR = Token{SQLTokenType::Clause, "OR"};
    const Token AS = Token{SQLTokenType::Clause, "AS"};

    // -- AGGREGATE FUNCTIONS

    const Token COUNT = Token{SQLTokenType::AggregateFunction, "COUNT"};
    const Token SUM = Token{SQLTokenType::AggregateFunction, "SUM"};
    const Token AVG = Token{SQLTokenType::AggregateFunction, "AVG"};
    const Token MIN = Token{SQLTokenType::AggregateFunction, "MIN"};
    const Token MAX = Token{SQLTokenType::AggregateFunction, "MAX"};

    // -- DELIMITERS

    const Token OpenParen = Token{SQLTokenType::Delimiter, "("};
    const Token CloseParen = Token{SQLTokenType::Delimiter, ")"};
    const Token Comma = Token{SQLTokenType::Delimiter, ","};
    const Token Semicolon = Token{SQLTokenType::Delimiter, ";"};
    const Token Period = Token{SQLTokenType::Delimiter, "."};

    // -- WILDCARD

    const Token Wildcard = Token{SQLTokenType::Wildcard, "*"};

    // -- OPERATOR

    const Token EQ = Token{SQLTokenType::Operator, "="};
    const Token NEQ = Token{SQLTokenType::Operator, "!="};
    const Token LEQ = Token{SQLTokenType::Operator, "<="};
    const Token GEQ = Token{SQLTokenType::Operator, ">="};
    const Token LT = Token{SQLTokenType::Operator, "<"};
    const Token GT = Token{SQLTokenType::Operator, ">"};

    // -- TERMINAL
    const Token Terminator = Token{SQLTokenType::Terminator, "$"};
}

#endif