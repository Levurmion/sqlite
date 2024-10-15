#ifndef SQL_LEXER
#define SQL_LEXER

#include "tokens.hpp"
#include <iostream>

class SQLLexer {

    private:
        std::unordered_map<TokenType, std::regex> tokenMap;

    public:
        SQLLexer(std::unordered_map<TokenType, std::regex> tokenMap);

        std::vector<Token> tokenize(const std::string& commands);
};


#endif