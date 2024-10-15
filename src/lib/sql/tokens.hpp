#ifndef SQL_TOKENS
#define SQL_TOKENS

#include <iostream>
#include <string>
#include <regex>

enum class TokenType {
    Keyword,
    Identifier,
    Punctuation,
    AggregateFunction,
    Wildcard,
};

struct Token {
    TokenType type;
    std::string value;
};

const std::unordered_map<TokenType, std::regex> TOKENS = {
    {TokenType::Keyword, std::regex(R"(\bSELECT|FROM|WHERE|INSERT|UPDATE|DELETE|JOIN|AND|OR\b)", std::regex_constants::icase)},
    {TokenType::AggregateFunction, std::regex(R"(\bCOUNT|SUM|AVG|MIN|MAX\b)", std::regex_constants::icase)},
    {TokenType::Identifier, std::regex(R"([A-Za-z_][A-Za-z0-9_]*)")},
    {TokenType::Punctuation, std::regex(R"([\(\),;.])")},
    {TokenType::Wildcard, std::regex(R"(\*)")}
};

#endif