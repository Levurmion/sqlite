#include "lexer.hpp"
#include "tokens.hpp"
#include <iostream>
#include <regex>


SQLLexer::SQLLexer(std::vector<std::tuple<SQLTokenType, std::regex>> tokenList): tokenList(tokenList) {};


std::vector<Token> SQLLexer::tokenize(const std::string& command) {
    std::vector<Token> tokens;
    std::string::const_iterator start = command.begin();
    std::string::const_iterator end = command.end();

    while (start != end) {
        // skip whitespaces
        if (std::isspace(*start)) {
            ++start;
            continue;
        }

        bool matchFound = false;

        // iterate over our tokenList to try and match the string starting at `start`
        // with a valid token pattern
        for (auto& [tokenType, pattern]: tokenList) {
            std::smatch match;

            // if we find a matching token
            if (std::regex_search(start, end, match, pattern, std::regex_constants::match_continuous)) {
                std::string value = match.str();
                start += match.length();
                matchFound = true;
                tokens.push_back({tokenType, value});
                break;
            }
        }

        if (!matchFound) {
            std::cerr << "Unrecognized character near: " << *start << std::endl;
            ++start; 
        }
    };

    std::vector<Token> processedTokens;
    processedTokens.reserve(tokens.size());
    for (auto token: tokens) {
        if (token.type == SQLTokenType::Delimiter && token.value == ",") {
            continue;
        } else {
            processedTokens.push_back(token);
        }
    }

    processedTokens.push_back({SQLTokenType::Terminator, "$"});

    return processedTokens;
}