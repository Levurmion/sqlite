#include "strings.hpp"
#include <iostream>

bool startsWith (std::string string, std::string prefix) {
    if (prefix.length() > string.length()) {
        return false;
    }
    for (int i = 0; i < prefix.length(); i++) {
        if (string[i] != prefix[i]) {
            return false;
        }
    }
    return true;
};

bool endsWith (std::string string, std::string suffix) {
    if (suffix.length() > string.length()) {
        return false;
    }
    int suffixStartIdx = string.length() - suffix.length();
    for (int i = suffixStartIdx; i < string.length(); i++) {
        int suffixIdx = i - suffix.length();
        if (string[i] != suffix[suffixIdx]) {
            return false;
        }
    }
    return true;
};
