/**
 * @file Reservoir.h
 * @brief Contains the declaration of the Reservoir class.
 *
 * This header file declares the Reservoir class, which represents a Portuguese water reservoir.
 * Each reservoir has a name, a municipality, an ID, a code, and a maximum delivery capacity.
 */

#ifndef PROJ_DA_01_RESERVOIR_H
#define PROJ_DA_01_RESERVOIR_H

#include "Code.h"

/**
 * @class Reservoir
 * @brief Represents a Portuguese water reservoir.
 *
 * Each reservoir has a name, a municipality, an ID, a code, and a maximum delivery capacity.
 */
class Reservoir {
public:
    /**
     * @brief Default constructor for the Reservoir class.
     */
    Reservoir();

    /**
     * @brief Constructs a Reservoir object with the given parameters.
     * @param name The name of the reservoir.
     * @param municipality The municipality where the reservoir is located.
     * @param id The ID of the reservoir.
     * @param code The code of the reservoir.
     * @param maxDelivery The maximum delivery capacity of the reservoir.
     */
    Reservoir(std::string name, std::string municipality, int id, Code code, int maxDelivery);

    /**
     * @brief Gets the name of the reservoir.
     * @return The name of the reservoir.
     */
    const std::string getName() const;

    /**
     * @brief Sets the name of the reservoir.
     * @param name The name of the reservoir.
     */
    void setName(const std::string& name);

    /**
     * @brief Gets the municipality where the reservoir is located.
     * @return The municipality of the reservoir.
     */
    const std::string getMunicipality() const;

    /**
     * @brief Sets the municipality where the reservoir is located.
     * @param municipality The municipality of the reservoir.
     */
    void setMunicipality(const std::string& municipality);

    /**
     * @brief Gets the ID of the reservoir.
     * @return The ID of the reservoir.
     */
    int getId() const;

    /**
     * @brief Sets the ID of the reservoir.
     * @param id The ID of the reservoir.
     */
    void setId(const int& id);

    /**
     * @brief Gets the code of the reservoir.
     * @return The code of the reservoir.
     */
    Code getCode() const;

    /**
     * @brief Sets the code of the reservoir.
     * @param code The code of the reservoir.
     */
    void setCode(const Code& code);

    /**
     * @brief Gets the maximum delivery capacity of the reservoir.
     * @return The maximum delivery capacity of the reservoir.
     */
    int getMaxDelivery() const;

    /**
     * @brief Sets the maximum delivery capacity of the reservoir.
     * @param maxDelivery The maximum delivery capacity of the reservoir.
     */
    void setMaxDelivery(const int& maxDelivery);
private:
    std::string name;           ///< The name of the reservoir.
    std::string municipality;   ///< The municipality where the reservoir is located.
    int id;                     ///< The ID of the reservoir.
    Code code;                  ///< The code of the reservoir.
    int maxDelivery;            ///< The maximum water delivery capacity of the reservoir in m^3 / sec.
};

#endif //PROJ_DA_01_RESERVOIR_H
