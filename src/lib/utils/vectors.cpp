#include <iostream>

template<typename T>
std::vector<T> slice(const std::vector<T>& v, int start, int end) {
    // Ensure valid range
    if (start < 0 || end > v.size() || start > end) {
        throw std::out_of_range("Invalid slice range");
    }

    // Create a new vector from the subrange [start, end)
    return std::vector<T>(v.begin() + start, v.begin() + end);
}