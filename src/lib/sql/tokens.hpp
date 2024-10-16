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
    Terminator,
};

struct Token {
    SQLTokenType type;
    std::string value;
};

const std::unordered_map<SQLTokenType, std::regex> TOKENS = {
    {SQLTokenType::Clause, std::regex(R"(\bSELECT|FROM|WHERE|CREATE|INSERT|UPDATE|DELETE|JOIN|AND|OR\b)", std::regex_constants::icase)},
    {SQLTokenType::AggregateFunction, std::regex(R"(\bCOUNT|SUM|AVG|MIN|MAX\b)", std::regex_constants::icase)},
    {SQLTokenType::Identifier, std::regex(R"([A-Za-z_][A-Za-z0-9_]*)")},
    {SQLTokenType::Delimiter, std::regex(R"([\(\),;.])")},
    {SQLTokenType::Wildcard, std::regex(R"(\*)")},
    {SQLTokenType::Operator, std::regex(R"(=|!=|<=|>=|<|>)")},
};

#endif