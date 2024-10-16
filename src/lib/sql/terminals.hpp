#ifndef SQL_TERMINALS
#define SQL_TERMINALS

#include "parser.hpp"
#include "tokens.hpp"

typedef Terminal<SQLTokenType> SQLTerminal;

// CLAUSES
struct SELECT: SQLTerminal {
    SELECT(): SQLTerminal(SQLTokenType::Clause, "SELECT") {};
};
struct FROM: SQLTerminal {
    FROM(): SQLTerminal(SQLTokenType::Clause, "FROM") {};
};

// DELIMITERS
struct Semicolon: SQLTerminal {
    Semicolon(): SQLTerminal(SQLTokenType::Delimiter, ";") {};
};

// WILDCARD
struct Wildcard: SQLTerminal {
    Wildcard(): SQLTerminal(SQLTokenType::Wildcard, "*") {};
};

// IDENTIFIER
struct Identifier: SQLTerminal {
    Identifier(std::string value): SQLTerminal(SQLTokenType::Identifier, value) {};
};

#endif