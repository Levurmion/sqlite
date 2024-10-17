#ifndef SQL_TERMINALS
#define SQL_TERMINALS

#include "parser.hpp"
#include "tokens.hpp"

template<typename T>
struct Terminal: public Symbol {
    T type;
    explicit Terminal(T type, std::string value): Symbol(value), type(type) {};
    explicit Terminal(T type): type(type), Symbol("") {};
};


struct SQLTerminal: Terminal<SQLTokenType> {
    explicit SQLTerminal(SQLTokenType type, std::string value): Terminal(type, value) {};
    explicit SQLTerminal(const Token& token): Terminal(token.type, token.value) {};
    SQLTerminal(const SQLTerminal& other): Terminal(other.type, other.value) {};

    /**
     * Return pointer to a copy of the current `SQLTerminal` instance.
     */
    SQLTerminal* copy () const {
        return new SQLTerminal(this->type, this->value);
    }

    bool operator==(const SQLTerminal& other) const {
        return other.type == this->type && other.value == this->value;
    }
};


namespace SQLTerminals {

    // -- CLAUSES

    const SQLTerminal SELECT = SQLTerminal(SQLTokens::SELECT);
    const SQLTerminal FROM = SQLTerminal(SQLTokens::FROM);

    // -- DELIMITERS

    const SQLTerminal Semicolon = SQLTerminal(SQLTokens::Semicolon);
    const SQLTerminal Comma = SQLTerminal(SQLTokens::Comma);

    // -- WILDCARD

    const SQLTerminal Wildcard = SQLTerminal(SQLTokens::Wildcard);

    // -- Identifier
    const SQLTerminal Identifier = SQLTerminal(SQLTokenType::Identifier, "");

    // -- Epsilon
    const SQLTerminal Epsilon = SQLTerminal(SQLTokenType::Epsilon, "");
}

#endif