#ifndef DOT_COMMAND
#define DOT_COMMAND

#include <iostream>
#include <optional>

const int HEADER_SIZE = 100;
const int BTREE_HEADER_LEAF_SIZE = 8;
const int BTREE_HEADER_INTERIOR_SIZE = 12;

std::optional<std::string> getDotCommand (const std::vector<std::string>& positionalArgs);

// DOT COMMANDS

void dbinfo (std::ifstream& databaseFile);
void tables (std::ifstream& databaseFile);

#endif