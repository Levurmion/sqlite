#include <iostream>
#include "../utils/strings.cpp"

using namespace std;

enum class FlagAttributes {
    DB,
    UNKNOWN
};


class ArgParser {

    public:
        string db;

        ArgParser (int argc, char* argv[]) {

            FlagAttributes readingAttr = FlagAttributes::UNKNOWN;

            // skip first argv
            for (int i = 1; i < argc; i++) {
                string argString = string(argv[i]);
                
                // a short flag
                if (startsWith(argString, "-")) {
                    string flagName = argString.substr(1);
                    
                    if (flagName == "f") {
                        readingAttr = FlagAttributes::DB;
                    }

                // a long flag
                } else if (startsWith(argString, "--")) {
                    string flagName = argString.substr(2);

                    if (flagName == "file") {
                        readingAttr = FlagAttributes::DB;
                    }
                } else {

                    if (readingAttr == FlagAttributes::UNKNOWN) {
                        continue;
                    } else if (readingAttr == FlagAttributes::DB) {
                        db = argString;
                    }
                }
            }
        };
        ~ArgParser () {

        };

};