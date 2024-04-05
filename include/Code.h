/**
 * @file Code.h
 * @brief Contains the declaration of the Code class and related enums.
 *
 * This header file declares the Code class, which represents a code used for RESERVOIRS, PUMPING STATIONS and CITIES.
 * It also declares the CodeType enum, which specifies the type of a code (R, PS, C).
 */

#ifndef PROJ_DA_01_CODE_H
#define PROJ_DA_01_CODE_H

#include <string>
#include <iostream>

/**
 * @enum CodeType
 * @brief Enum class representing the type of a code.
 */
enum class CodeType { RESERVOIR, STATION, CITY };

/**
 * @class Code
 * @brief Represents a code used for Reservoir, Station and City.
 *
 * The code consists of a complete code string, a code type, and a ID number.
 */
class Code {
public:
    /**
     * @brief Default constructor for Code class.
     */
    Code();

    /**
     * @brief Constructs a Code object with the given code string.
     * @param code The code string.
     */
    Code(const std::string& code);

    /**
     * @brief Gets the complete code string.
     * @return The complete code string.
     */
    std::string getCompleteCode() const;

    /**
     * @brief Gets the type of the code.
     * @return The code type.
     */
    CodeType getType() const;

    /**
     * @brief Gets the ID number associated with the code.
     * @return The number.
     */
    int getNumber() const;

    /**
     * @brief Checks if this code is equal to another code.
     * @param other The other code to compare.
     * @return True if the codes are equal, false otherwise.
     */
    bool operator==(const Code& other) const;

private:
    std::string completeCode;   ///< The complete code string.
    CodeType type;              ///< The code type.
    int number;                 ///< The ID number associated with the code.
};

#endif //PROJ_DA_01_CODE_H