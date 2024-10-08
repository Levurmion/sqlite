#ifndef ARGPARSER
#define ARGPARSER

#include <iostream>

enum FlagType {
    SHORT,
    LONG,
    NONE
};

/**
 * The `ArgParser` class parses CLI arguments into a `std::unordered_map` and `std::vector` 
 * objects accessible through the following public attributes:
 * 
 * - `positional`: arguments passed with neither prefixes.
 * - `shortFlags`: flags prefixed with the double hyphen `--`.
 * - `longFlags`: flags prefixed with a single hypen `-` (restricted to single characters).
 * 
 * ### Parsing Rules
 * 
 * 1. `positional` arguments must be passed before any `flags`.
 * 2. `flags` passed without additional arguments will be assigned `string` `"true"` values.
 * 
 * ### Example
 * 
 * `./program path/to/input path/to/output --verbose --logs path/to/logfile`
 * 
 * Will return:
 * - `positional`: `["path/to/input", "path/to/output"]`
 * - `longFlags`: `{"verbose": "true", "logs": "path/to/logfile"}`
 */
class ArgParser {

    private:
        void setAsBoolFlag (std::string flagName, FlagType flagType);

    public:
        std::vector<std::string> positional;
        std::unordered_map<std::string, std::string> shortFlags;
        std::unordered_map<std::string, std::string> longFlags;

        ArgParser (int argc, const char* argv[]);

};

#endif