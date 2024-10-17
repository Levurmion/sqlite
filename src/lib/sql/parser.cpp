#include "parser.hpp"
#include "tokens.hpp"
#include "terminals.hpp"
#include <iostream>
#include <string>


SQLParser::SQLParser(Symbol* startExpression): parseTree(startExpression) {};

Token SQLParser::currentToken() const {
    if (tokenPtr <= tokenStream.size() - 1) {
        return tokenStream[tokenPtr];
    } else {
        throw std::out_of_range("`tokenPtr` out of range.");
    }
}

Symbol* SQLParser::getTopSymbol() const {
    if (pushdownStack.size() > 0) {
        return pushdownStack[pushdownStack.size() - 1];
    } else {
        return nullptr;
    }
};

void SQLParser::matchToken(Token& token) {
    auto topSymbol = getTopSymbol();
    SQLTerminal* pTopSqlTerminal = dynamic_cast<SQLTerminal*>(topSymbol);

    if (pTopSqlTerminal == nullptr) {
        std::cerr << "Syntax error near: " << token.value << std::endl;
        return;
    } else if (token.type == SQLTokenType::Identifier && pTopSqlTerminal->type == SQLTokenType::Identifier) {
        // matched identifier
        pushdownStack.pop_back();
    } else if (token.type == pTopSqlTerminal->type && token.value == pTopSqlTerminal->value) {
        // matched another terminal symbol
        pushdownStack.pop_back();
    }
};

void SQLParser::parseTokenStream(const std::vector<Token>& tokenStream) {

}