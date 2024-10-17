#ifndef SQL_LEXER
#define SQL_LEXER

#include "tokens.hpp"
#include <iostream>

class SQLLexer {

    private:
        std::vector<std::tuple<SQLTokenType, std::regex>> tokenList;

    public:
        SQLLexer(std::vector<std::tuple<SQLTokenType, std::regex>> tokenList);

        std::vector<Token> tokenize(const std::string& commands);
};


#endif