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
struct Terminal: public Symbol {
    T type;
    explicit Terminal(T type, std::string value): Symbol(value), type(type) {};
    explicit Terminal(T type): type(type), Symbol("") {};
};


// An LL(1) parser for SQL statements.
class SQLParser {
    private:
        int tokenPtr = 0;
        std::vector<Token> tokenStream;
        std::vector<Symbol*> pushdownStack;

        /**
         * Returns the current token pointed to by `this->tokenPtr`.
         */
        Token currentToken() const;

        /**
         * Get the `Symbol` on top of the `pushdownStack`.
         */
        Symbol* getTopSymbol () const;

        /**
         * Attempts to match a `Token` with an `SQLTerminal`. 
         */
        void matchToken(Token& token);
    
    public:
        Symbol* parseTree;

        explicit SQLParser (Symbol* startExpression);
        void parseTokenStream(const std::vector<Token>& tokenStream);
};


#endif