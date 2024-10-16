#ifndef SQL_PARSER
#define SQL_PARSER

#include "tokens.hpp"
#include <iostream>
#include <string>

struct Symbol {
    std::string value;
    explicit Symbol(std::string value): value(value) {};
    virtual ~Symbol() = default;
};

template<typename T>
struct Terminal: Symbol {
    T type;
    explicit Terminal(T type, std::string value): type(type), Symbol(value) {};
    explicit Terminal(T type): type(type), Symbol("") {};
};


struct NonTerminal: Symbol {
    std::vector<Symbol*> children;
    explicit NonTerminal(std::string value): Symbol(value) {};

    /**
     * Subclasses must implement the production rules of this `NonTerminal` symbol.
     */
    virtual std::vector<Symbol*> productionRule (const Token& token) const;
};


struct Epsilon: Symbol {
    explicit Epsilon(): Symbol("") {};
};


class LL1SQLParser {
    private:
        std::vector<Symbol*> symbolStack;

};


#endif