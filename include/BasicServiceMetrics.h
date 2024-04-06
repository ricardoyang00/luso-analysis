/**
 * @file BasicServiceMetrics.h
 * @brief Contains the declaration of the BasicServiceMetrics class.
 *
 * This header file declares the BasicServiceMetrics class, which provides functionality for calculating basic service metrics
 * related to water distribution in a graph.
 */

#ifndef FEUP_DA_01_BASICSERVICEMETRICS_H
#define FEUP_DA_01_BASICSERVICEMETRICS_H

#include "ParseData.h"
#include <map>

/**
 * @class BasicServiceMetrics
 * @brief Class for calculating basic service metrics related to water distribution.
 *
 * The BasicServiceMetrics class provides functionality for calculating basic service metrics
 * related to water distribution in a water supply network.
 */
class BasicServiceMetrics {
private:
    Graph<Code> originalCodeGraph;          /**< Original code graph for water distribution. */
    Graph<Code> codeGraphCopy;              /**< Copy of the code graph for water distribution. */
    const DataContainer& dataContainer;     /**< Reference to the data container for storing water distribution data. */

    /**
     * @brief Tests and visits a vertex in the residual graph during the Edmonds-Karp algorithm.
     * @param q Queue of vertices to visit.
     * @param e Edge to visit.
     * @param w Vertex to visit.
     * @param residual Residual value of the edge.
     *
     * Time Complexity: O(1)
     */
    static void testAndVisit(std::queue<Vertex<Code>*>& q, Edge<Code>* e, Vertex<Code>* w, double residual);

    /**
     * @brief Finds an augmenting path in the residual graph during the Edmonds-Karp algorithm.
     * @param s Source vertex.
     * @param t Target vertex.
     * @return True if an augmenting path is found, false otherwise.
     *
     * Time Complexity: O(V + E)
     */
    bool findAugmentingPath(Vertex<Code>* s, Vertex<Code>* t);

    /**
     * @brief Finds the bottleneck value along an augmenting path during the Edmonds-Karp algorithm.
     * @param s Source vertex.
     * @param t Target vertex.
     * @return Bottleneck value along the augmenting path.
     *
     * Time Complexity: O(V)
     */
    static double findBottleNeckValue(Vertex<Code>* s, Vertex<Code>* t);

    /**
     * @brief Augments the flow along an augmenting path during the Edmonds-Karp algorithm.
     * @param s Source vertex.
     * @param t Target vertex.
     * @param bnValue Bottleneck value.
     *
     * Time Complexity: O(V)
     */
    static void augmentFlowAlongPath(Vertex<Code>* s, Vertex<Code>* t, double bnValue);

    /**
     * @brief Calculates and returns the remaining water that can be pumped from reservoirs to connected pipes.
     *
     * This function iterates through each vertex in the code graph copy, checks if it represents a reservoir (excluding the super reservoir),
     * and calculates the remaining water that can be pumped from it to connected pipes based on its maximum delivery capacity.
     * It updates the flow on the edges accordingly and returns a mapping of destination vertices to the amount of extra flow received.
     *
     * @return An unordered map containing destination vertices as keys and the amount of extra flow received from reservoirs as values.
     */
    std::unordered_map<Vertex<Code>*, double> pumpRemainingWaterFromReservoirs();

    /**
     * @brief Distributes extra flow received from origin vertex and distributes to its destiny vertices based on their flow ratios.
     *
     * This function takes a vertex and the amount of extra flow received from it.
     * It calculates the remaining capacity of each connected pipe and sorts them based on their flow / weight ratios.
     * The extra flow is then distributed to pipes with lower flow ratios first, ensuring a balanced distribution.
     * It recursively distributes the remaining extra flow to downstream vertices as needed.
     *
     * @param vertex Pointer to the vertex that received flow.
     * @param extraFlow The amount of extra flow received from the origin vertex.
     */
    void distributeExtraFlow(Vertex<Code>* vertex, double extraFlow);
public:
    /**
     * @brief Constructor for the BasicServiceMetrics class.
     * @param codeGraph The code graph representing water distribution.
     * @param dataContainer The data container storing water distribution data.
     */
    BasicServiceMetrics(const Graph<Code>& codeGraph, const DataContainer& dataContainer);

    /**
     * @brief Gets the graph used for basic service metrics calculations.
     * @return Reference to the graph used for basic service metrics calculations.
     *
     * Time Complexity: O(1)
     */
    Graph<Code>& getBSMGraph();

    /**
     * @brief Resets the graph used for basic service metrics calculations.
     *
     * Time Complexity: O(V * E^2)
     */
    void resetBSMGraph();

    /**
     * @brief Runs the Edmonds-Karp algorithm to find the maximum flow in the graph.
     *
     * Time Complexity: O(V * E^2)
     */
    void edmondsKarp();

    /**
     * @brief Calculates and returns the total maximum flow in the system.
     * @return Total maximum flow in the system.
     *
     * Time Complexity: O(V + E)
     */
    double getTotalMaxFlow();

    /**
     * @brief Calculates and returns the flow to a specific city.
     * @param cityCode The code of the city.
     * @return Flow to the specified city.
     *
     * Time Complexity: O(V)
     */
    double getFlowToCity(const Code& cityCode);

    /**
     * @brief Retrieves the flows of all cities in the system.
     * @return Map containing the flow to each city.
     *
     * Time Complexity: O(C * V) (where C is the number of cities)
     */
    std::map<int,double> getCitiesFlow();

    /**
     * @brief Removes a reservoir from the system.
     * @param reservoirCode The code of the reservoir to remove.
     *
     * Time Complexity: O(V * E^2) (Edmonds-Karp dominant)
     */
    void removeReservoir(const Code& reservoirCode);

    /**
     * @brief Removes a pumping station from the system.
     * @param stationCode The code of the pumping station to remove.
     *
     * Time Complexity: O(V * E^2) (Edmonds-Karp dominant)
     */
    void removePumpingStation(const Code& stationCode);

    /**
     * @brief Removes pipes from the system.
     * @param pipeCodes Vector containing pairs of pipe codes to remove.
     *
     * Time Complexity: O(V * E^2) (Edmonds-Karp dominant)
     */
    void removePipes(const std::vector<std::pair<Code,Code>>& pipeCodes);

    /**
     * @brief Balances the flow by distributing extra flow received from reservoirs.
     *
     * This function calls the pumpRemainingWaterFromReservoirs() function to get the extra flow received from reservoirs
     * and then distributes this extra flow using the distributeExtraFlow() function.
     * It ensures a balanced distribution of extra flow throughout the network.
     */
    void balanceFlow();
};


#endif //FEUP_DA_01_BASICSERVICEMETRICS_H
