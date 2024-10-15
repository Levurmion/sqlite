#include "lexer.hpp"
#include "tokens.hpp"
#include <iostream>
#include <regex>


SQLLexer::SQLLexer(std::unordered_map<TokenType, std::regex> tokenMap): tokenMap(tokenMap) {};


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

        // iterate over our tokenMap to try and match the string starting at `start`
        // with a valid token pattern
        for (auto& [tokenType, pattern]: tokenMap) {
            std::smatch match;

            // if we find a matching token
            if (std::regex_search(start, end, match, pattern, std::regex_constants::match_continuous)) {
                std::string value = match.str();
                tokens.push_back({tokenType, value});
                start += match.length();
                matchFound = true;
                break;
            }
        }

        if (!matchFound) {
            std::cerr << "Unrecognized character near: " << *start << std::endl;
            ++start; 
        }
    };

    return tokens;
}