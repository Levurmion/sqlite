#include "parser.hpp"
#include "tokens.hpp"
#include "terminals.cpp"
#include "non-terminals.cpp"
#include <iostream>
#include <string>


SQLParser::SQLParser(NonTerminal* startExpression): startExpression(startExpression) {};

bool SQLParser::parseTokenStream(const std::vector<Token>& tokenStream) {
    this->tokenPtr = 0;
    this->tokenStream = tokenStream;
    
    if (this->parseTree != nullptr) {
        delete this->parseTree;
    }

    // assign a new copy of the startExpression
    auto sqlStartExpression = dynamic_cast<SQLNonTerminals::SQLStartExp*>(this->startExpression);
    if (sqlStartExpression != nullptr) {
        this->parseTree = sqlStartExpression->clone();
    } else {
        return false;
    }

    // build the parse tree
    this->buildParseTree(this->parseTree);

    // check the final lookAheadToken
    const auto lookAheadToken = this->tokenStream[this->tokenPtr];
    return lookAheadToken == SQLTokens::Terminator;
}


void SQLParser::buildParseTree(Symbol* pSymbol) {
    const auto lookAheadToken = this->tokenStream[this->tokenPtr];

    // terminate recursion on reaching a Terminal
    auto pTerminalSymbol = dynamic_cast<Terminal*>(pSymbol);
    if (pTerminalSymbol != nullptr) {
        if (*pTerminalSymbol == lookAheadToken) {
            if (pTerminalSymbol->type == SQLTokenType::Identifier) {
                pTerminalSymbol->value = lookAheadToken.value;
            }
            this->tokenPtr++;
        } else if (*pTerminalSymbol != SQLTerminals::Epsilon) {
            std::cerr << "Syntax error near: \"" << lookAheadToken.value << "\"" << std::endl;
            throw std::runtime_error("Syntax Error.");
        }
    }

    // recurse again if it is a NonTerminal
    auto pNonTerminalSymbol = dynamic_cast<NonTerminal*>(pSymbol);
    if (pNonTerminalSymbol != nullptr) {
        auto substitutions = pNonTerminalSymbol->productionRule(lookAheadToken);
        
        for (auto substitution: substitutions) {
            pNonTerminalSymbol->substitutions.push_back(substitution);
            buildParseTree(substitution);
        }
    }

    return;
}