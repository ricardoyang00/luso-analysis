#ifndef PROJ_DA_01_UTILITIES_H
#define PROJ_DA_01_UTILITIES_H

#include <iostream>
#include <algorithm>
#include <sstream>

std::string TrimString(const std::string& toTrim);

/**
 * @brief Formats a value in bold for terminal output.
 * @param value The value to be formatted.
 * @return The formatted value in bold.
 */
template <typename T>
std::string makeBold(const T& value) {
    std::ostringstream oss;
    oss << "\033[1m" << value << "\033[0m";
    return oss.str();
};


#endif //PROJ_DA_01_UTILITIES_H
