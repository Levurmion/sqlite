#include <iostream>
#include <stdexcept>
#include "../utils/strings.cpp"

enum class FlagType {
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
        void setAsBoolFlag (std::string flagName, FlagType flagType) {
            if (flagType == FlagType::SHORT) {
                shortFlags[flagName] = "true";
            } else if (flagType == FlagType::LONG) {
                longFlags[flagName] = "true";
            }
        }

    public:
        std::vector<std::string> positional;
        std::unordered_map<std::string, std::string> shortFlags;
        std::unordered_map<std::string, std::string> longFlags;

        ArgParser (int argc, char* argv[]) {

            std::string currFlag;
            FlagType flagType = FlagType::NONE;

            for (int i = 1; i < argc; i++) {
                std::string stringArg = std::string(argv[i]);
                // a longFlag argument
                if (startsWith(stringArg, "--")) {
                    if (!currFlag.empty()) {
                        setAsBoolFlag(currFlag, flagType);
                    }
                    currFlag = stringArg.substr(2);
                    flagType = FlagType::LONG;

                // a shortFlag argument
                } else if (startsWith(stringArg, "-")) {
                    if (!currFlag.empty()) {
                        setAsBoolFlag(currFlag, flagType);
                    }
                    currFlag = stringArg.substr(1);
                    flagType = FlagType::SHORT;

                // a positional argument or value
                } else {
                    // valid positional argument
                    if (shortFlags.empty() && longFlags.empty() && currFlag.empty()) {
                        positional.push_back(stringArg);

                    // no flags were encountered before this
                    // shortFlags || longFlags is not empty
                    // invalid format!
                    } else if (flagType == FlagType::NONE) {
                        std::cerr << "Positional arguments must preceed flags." << std::endl;
                        throw new std::invalid_argument(
                            "Positional arguments must preceed flags"
                        );
                    } else if (flagType == FlagType::SHORT) {
                        shortFlags[currFlag] = stringArg;
                    } else if (flagType == FlagType::LONG) {
                        longFlags[currFlag] = stringArg;
                    }

                    flagType = FlagType::NONE;
                    currFlag = "";
                }
            }

            // dangling flag
            if (flagType != FlagType::NONE && !currFlag.empty()) {
                setAsBoolFlag(currFlag, flagType);
            }
        };
        ~ArgParser () {};

};