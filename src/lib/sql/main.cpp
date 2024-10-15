#include "lexer.hpp"
#include "tokens.hpp"
#include <iostream>
#include <string>

int main () {

    std::string command = "SELECT COUNT(*) FROM this_table;";
    SQLLexer lexer = SQL_LEXER(TOKENS);
    std::vector<Token> tokens = lexer.tokenize(command);

    for (auto& token: tokens) {
        std::cout << "Found token: " <<  token.value << std::endl;
    }

    return 0;
}