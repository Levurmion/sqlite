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

struct Token {
    SQLTokenType type;
    std::string value;

    bool operator==(const Token& other) const {
        return other.type == this->type && other.value == this->value;
    }
};

namespace std {
    /**
     * The STL `std::hash` function is defined as a functor - a function object where the
     * the call operator `()` is overriden as a pure function.
     */
    template <>
    struct hash<Token> {
        std::size_t operator()(const Token& token) const {
            // Use the hash functions for built-in types and combine them
            return std::hash<SQLTokenType>()(token.type) ^ (std::hash<std::string>()(token.value) << 1);
        }
    };
};

const std::unordered_map<SQLTokenType, std::regex> TOKENS = {
    {SQLTokenType::Clause, std::regex(R"(\bSELECT|FROM|WHERE|CREATE|INSERT|UPDATE|DELETE|JOIN|AND|OR|AS\b)", std::regex_constants::icase)},
    {SQLTokenType::AggregateFunction, std::regex(R"(\bCOUNT|SUM|AVG|MIN|MAX\b)", std::regex_constants::icase)},
    {SQLTokenType::Identifier, std::regex(R"([A-Za-z_][A-Za-z0-9_]*)")},
    {SQLTokenType::Delimiter, std::regex(R"([\(\),;.])")},
    {SQLTokenType::Wildcard, std::regex(R"(\*)")},
    {SQLTokenType::Operator, std::regex(R"(=|!=|<=|>=|<|>)")},
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

}

#endif