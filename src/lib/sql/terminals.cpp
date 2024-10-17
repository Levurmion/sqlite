#ifndef SQL_TERMINALS
#define SQL_TERMINALS

#include "parser.hpp"
#include "tokens.hpp"


namespace SQLTerminals {

    // -- CLAUSES

    const Terminal SELECT = Terminal(SQLTokens::SELECT);
    const Terminal FROM = Terminal(SQLTokens::FROM);

    // -- DELIMITERS

    const Terminal Semicolon = Terminal(SQLTokens::Semicolon);
    const Terminal Comma = Terminal(SQLTokens::Comma);

    // -- WILDCARD

    const Terminal Wildcard = Terminal(SQLTokens::Wildcard);

    // -- Identifier
    const Terminal Identifier = Terminal(SQLTokenType::Identifier, "");

    // -- Epsilon
    const Terminal Epsilon = Terminal(SQLTokenType::Epsilon, "");
}

#endif