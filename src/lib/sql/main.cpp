#include "lexer.hpp"
#include "tokens.hpp"
#include "parser.hpp"
#include "non-terminals.cpp"
#include "terminals.hpp"
#include <iostream>
#include <string>


int main () {

    std::string command = "SELECT type, name, tbl_name FROM this_table;";
    SQLLexer lexer = SQLLexer(TOKENS);
    std::vector<Token> tokens = lexer.tokenize(command);
    SQLStartExp sqlStartExp = SQLStartExp();
    SQLParser parser = SQLParser(&sqlStartExp);

    for (auto& token: tokens) {
        std::cout << "Found token: " <<  token.value << std::endl;
    }

    return 0;
}