/**
 * @file Utilities.h
 * @brief Contains utility functions for string manipulation.
 *
 * This header file provides various utility functions used for string manipulation.
 * Functions include string trimming and formatting text in bold for terminal output.
 */

#ifndef PROJ_DA_01_UTILITIES_H
#define PROJ_DA_01_UTILITIES_H

#include <iostream>
#include <algorithm>
#include <sstream>

/**
 * @brief Trim whitespace from the beginning and end of a string.
 * @param toTrim The string to be trimmed.
 * @return The trimmed string.
 */
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
