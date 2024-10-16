#ifndef SQL_NON_TERMINALS
#define SQL_NON_TERMINALS

#include "parser.hpp"
#include "terminals.hpp"

// QUERIES
struct SelectQueryExp: NonTerminal {
    explicit SelectQueryExp(): NonTerminal("<select_query_exp>") {};

    std::vector<Symbol*> productionRule(const Token& token) const override {
        std::vector<Symbol*> products;

        if (token.type == SQLTokenType::Delimiter && token.value == "SELECT") {
            SelectClauseExp* selectClauseExp = new SelectClauseExp();
            products.push_back(selectClauseExp);
            FromClauseExp* fromClauseExp = new FromClauseExp();
            products.push_back(fromClauseExp);
            Semicolon* semicolon = new Semicolon();
            products.push_back(semicolon);

        }
        return products;
    };
};


// CLAUSES
struct SelectClauseExp: NonTerminal {
    explicit SelectClauseExp(): NonTerminal("<select_clause_exp>") {};

    std::vector<Symbol*> productionRule(const Token& token) const override {
        std::vector<Symbol*> products;

        if (token.type == SQLTokenType::Delimiter && token.value == "SELECT") {
            ColumnExp* columnExp = new ColumnExp();
            SELECT* select = new SELECT();
            products.push_back(columnExp);
            products.push_back(select);

        }
        return products;
    };
};

struct FromClauseExp: NonTerminal {
    explicit FromClauseExp(): NonTerminal("<from_clause_exp>") {};

    std::vector<Symbol*> productionRule(const Token& token) const override {
        std::vector<Symbol*> products;

        if (token.type == SQLTokenType::Delimiter && token.value == "FROM") {
            Identifier* id = new Identifier("");
            FROM* from = new FROM();
            products.push_back(id);
            products.push_back(from);

        }
        return products;
    };
};


// COLUMN EXPRESSIONS
struct ColumnExp: NonTerminal {
    explicit ColumnExp(): NonTerminal("<column_exp>") {};

    std::vector<Symbol*> productionRule(const Token& token) const override {
        std::vector<Symbol*> products;

        if (token.type == SQLTokenType::Identifier) {
            AdditionalColumnExp* additionalColumnExp = new AdditionalColumnExp();
            Identifier* id = new Identifier(token.value);
            products.push_back(additionalColumnExp);
            products.push_back(id);

        } else if (token.type == SQLTokenType::Wildcard) {
            Wildcard* wildcard = new Wildcard();
            products.push_back(wildcard);

        }
        return products;
    }
};

struct AdditionalColumnExp: NonTerminal {
    explicit AdditionalColumnExp(): NonTerminal("<additional_column_exp>") {};

    std::vector<Symbol*> productionRule(const Token& token) const override {
        std::vector<Symbol*> products;

        if (token.type == SQLTokenType::Delimiter && token.value == "FROM") {
            Epsilon* epsilon = new Epsilon();
            products.push_back(epsilon);

        } else if (token.type == SQLTokenType::Identifier) {
            AdditionalColumnExp* additionalColumnExp = new AdditionalColumnExp();
            Identifier* id = new Identifier(token.value);
            products.push_back(additionalColumnExp);
            products.push_back(id);

        }
        return products;
    };
};

#endif