#include "lexer.hpp"
#include "tokens.hpp"
#include "parser.hpp"
#include "non-terminals.cpp"
#include "terminals.cpp"
#include <iostream>
#include <string>


int main () {

    std::string command = "SELECT type, name, tabular, tbl_name FROM howdy;";
    SQLLexer lexer = SQLLexer(TOKENS);
    std::vector<Token> tokens = lexer.tokenize(command);

    for (auto token: tokens) {
        std::cout << "Token: ";
        std::cout << token.type << " ";
        std::cout << token.value << std::endl;
    }

    SQLNonTerminals::SQLStartExp startExpression = SQLNonTerminals::SQLStartExp();
    SQLParser parser = SQLParser(&startExpression);

    bool isSuccess = parser.parseTokenStream(tokens);
    std::cout << "Parsing success: " << isSuccess << std::endl;

    return 0;
}