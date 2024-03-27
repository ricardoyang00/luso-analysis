#ifndef FEUP_DA_01_BASICSERVICEMETRICS_H
#define FEUP_DA_01_BASICSERVICEMETRICS_H

#include "ParseData.h"

class BasicServiceMetrics {
private:
    Graph<Code> codeGraphCopy;
    const DataContainer& dataContainer;
    void testAndVisit(std::queue<Vertex<Code>*>& q, Edge<Code>* e, Vertex<Code>* w, double residual);
    bool findAugmentingPath(Vertex<Code>* s, Vertex<Code>* t);
    double findBottleNeckValue(Vertex<Code>* s, Vertex<Code>* t);
    void augmentFlowAlongPath(Vertex<Code>* s, Vertex<Code>* t, double bnValue);
    void addSuperSource();
    void addSuperSink();
public:
    BasicServiceMetrics(const Graph<Code>& codeGraph, const DataContainer& dataContainer);
    void edmondsKarp();
    double getTotalMaxFlow();
    static void printHeader();
    static void printCityMaxFlow(const std::string& name, const std::string& code, const double& maxFlow);
    void printEachCityMaxFlow();
    void printSpecificCityMaxFlow(const Code& city);
};


#endif //FEUP_DA_01_BASICSERVICEMETRICS_H
