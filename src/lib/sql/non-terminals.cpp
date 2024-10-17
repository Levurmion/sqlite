#include "parser.hpp"
#include "terminals.cpp"

namespace SQLNonTerminals{

    // COLUMN EXPRESSIONS
    struct AdditionalColumnExp: NonTerminal {
        explicit AdditionalColumnExp(): NonTerminal("<additional_column_exp>") {};

        std::vector<Symbol*> productionRule(const Token& token) const override {
            std::vector<Symbol*> products;

            if (token == SQLTokens::FROM) {
                auto Epsilon = SQLTerminals::Epsilon.clone();
                products.push_back(Epsilon);

            } else if (token.type == SQLTokenType::Identifier) {
                auto Identifier = SQLTerminals::Identifier.clone();
                products.push_back(Identifier);
                AdditionalColumnExp* additionalColumnExp = new AdditionalColumnExp();
                products.push_back(additionalColumnExp);

            }
            return products;
        };
    };

    struct ColumnExp: NonTerminal {
        explicit ColumnExp(): NonTerminal("<column_exp>") {};

        std::vector<Symbol*> productionRule(const Token& token) const override {
            std::vector<Symbol*> products;

            if (token.type == SQLTokenType::Identifier) {
                auto Identifier = SQLTerminals::Identifier.clone();
                products.push_back(Identifier);
                AdditionalColumnExp* additionalColumnExp = new AdditionalColumnExp();
                products.push_back(additionalColumnExp);

            } else if (token == SQLTokens::Wildcard) {
                auto Wildcard = SQLTerminals::Wildcard.clone();
                products.push_back(Wildcard);

            }
            return products;
        }
    };

    // CLAUSES
    struct FromClauseExp: NonTerminal {
        explicit FromClauseExp(): NonTerminal("<FROM_clause_exp>") {};

        std::vector<Symbol*> productionRule(const Token& token) const override {
            std::vector<Symbol*> products;

            if (token == SQLTokens::FROM) {
                auto FROM = SQLTerminals::FROM.clone();
                products.push_back(FROM);
                auto Identifier = SQLTerminals::Identifier.clone();
                products.push_back(Identifier);

            }
            return products;
        };
    };

    struct SelectClauseExp: NonTerminal {
        explicit SelectClauseExp(): NonTerminal("<SELECT_clause_exp>") {};

        std::vector<Symbol*> productionRule(const Token& token) const override {
            std::vector<Symbol*> products;

            if (token == SQLTokens::SELECT) {
                auto select = SQLTerminals::SELECT.clone();
                products.push_back(select);
                ColumnExp* columnExp = new ColumnExp();
                products.push_back(columnExp);

            }
            return products;
        };
    };

    // QUERIES
    struct SelectQueryExp: NonTerminal {
        explicit SelectQueryExp(): NonTerminal("<SELECT_query_exp>") {};

        std::vector<Symbol*> productionRule(const Token& token) const override {
            std::vector<Symbol*> products;

            if (token == SQLTokens::SELECT) {
                SelectClauseExp* selectClauseExp = new SelectClauseExp();
                products.push_back(selectClauseExp);
                FromClauseExp* fromClauseExp = new FromClauseExp();
                products.push_back(fromClauseExp);
                auto semicolon = SQLTerminals::Semicolon.clone();
                products.push_back(semicolon);

            }
            return products;
        };
    };

    // START
    struct SQLStartExp: NonTerminal {
        explicit SQLStartExp(): NonTerminal("<SQL_start_exp>") {};

        std::vector<Symbol*> productionRule(const Token& token) const override {
            std::vector<Symbol*> products;

            if (token == SQLTokens::SELECT) {
                SelectQueryExp* selectQueryExp = new SelectQueryExp();
                products.push_back(selectQueryExp);
            }
            return products;
        }

        SQLStartExp* clone() const override {
            return new SQLStartExp(*this);
        }
    };
}