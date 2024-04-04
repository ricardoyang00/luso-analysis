#ifndef FEUP_DA_01_BASICSERVICEMETRICS_H
#define FEUP_DA_01_BASICSERVICEMETRICS_H

#include "ParseData.h"
#include <map>

class BasicServiceMetrics {
private:
    Graph<Code> originalCodeGraph;
    Graph<Code> codeGraphCopy;
    const DataContainer& dataContainer;
    static void testAndVisit(std::queue<Vertex<Code>*>& q, Edge<Code>* e, Vertex<Code>* w, double residual);
    bool findAugmentingPath(Vertex<Code>* s, Vertex<Code>* t);
    static double findBottleNeckValue(Vertex<Code>* s, Vertex<Code>* t);
    static void augmentFlowAlongPath(Vertex<Code>* s, Vertex<Code>* t, double bnValue);

public:
    BasicServiceMetrics(const Graph<Code>& codeGraph, const DataContainer& dataContainer);
    Graph<Code>& getBSMGraph();
    void resetBSMGraph();
    void edmondsKarp();
    double getTotalMaxFlow();

    double getFlowToCity(const Code& cityCode);
    std::map<int,double> getCitiesFlow();

    void removeReservoir(const Code& reservoirCode);
    void removePumpingStation(const Code& stationCode);
    void removePipes(std::vector<std::pair<Code,Code>> pipeCodes);
};


#endif //FEUP_DA_01_BASICSERVICEMETRICS_H
