#ifndef SQL_PARSER
#define SQL_PARSER

#include "tokens.hpp"
#include <iostream>
#include <string>

struct Symbol {
    std::string value;
    explicit Symbol(std::string value): value(value) {};
    virtual ~Symbol() = default;
    
    /**
     * Return a pointer to a clone of this instance. 
     */
    virtual Symbol* clone() const {
        return new Symbol(*this);
    }
};


// A non-terminal symbol for the CFG.
struct NonTerminal: public Symbol {
    std::vector<Symbol*> substitutions;
    explicit NonTerminal(std::string value): Symbol(value) {};
    ~NonTerminal() {
        for (auto substitution: substitutions) {
            delete substitution;
        }
    };

    /**
     * Subclasses must implement the production rules of this `NonTerminal` symbol.
     */
    virtual std::vector<Symbol*> productionRule (const Token& token) const = 0;
};


// A terminal symbol of the CFG.
struct Terminal: Symbol {
    SQLTokenType type;
    explicit Terminal(SQLTokenType type, std::string value): Symbol(value), type(type) {};
    explicit Terminal(const Token& token): Terminal(token.type, token.value) {};
    Terminal(const Terminal& other): Terminal(other.type, other.value) {};

    Terminal* clone() const override {
        return new Terminal(*this);
    };

    // operator== overloads to compare terminal with token
    bool operator==(const Terminal& other) const {
        return other.type == this->type && other.value == this->value;
    };

    bool operator!=(const Terminal& other) const {
        return other.type != this->type || other.value != this->value;
    };

    friend bool operator==(const Terminal& terminal, const Token& token) {
        if (terminal.type == SQLTokenType::Identifier && token.type == SQLTokenType::Identifier) {
            return true;
        } else {
            return terminal.type == token.type && terminal.value == token.value;
        }
    };

    friend bool operator==(const Token& token, const Terminal& terminal) {
        if (terminal.type == SQLTokenType::Identifier && token.type == SQLTokenType::Identifier) {
            return true;
        } else {
            return terminal.type == token.type && terminal.value == token.value;
        }
    };
};


// An LL(1) parser for SQL statements.
class SQLParser {
    private:
        int tokenPtr = 0;
        std::vector<Token> tokenStream;
        NonTerminal* startExpression;

        void buildParseTree (Symbol* symbol);
    
    public:
        NonTerminal* parseTree = nullptr;

        explicit SQLParser (NonTerminal* startExpression);

        /**
         * Parse a token stream using the startExpression for the CFG. Will return
         * a boolean to indicate whether parsing has been successful or not.
         */
        bool parseTokenStream(const std::vector<Token>& tokenStream);
};


#endif