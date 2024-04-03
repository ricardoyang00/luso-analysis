#ifndef FEUP_DA_01_BASICSERVICEMETRICS_H
#define FEUP_DA_01_BASICSERVICEMETRICS_H

#include "ParseData.h"
#include <map>

class BasicServiceMetrics {
private:
    Graph<Code> originalCodeGraph;
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
    Graph<Code>& getBSMGraph();
    void resetBSMGraph();
    void edmondsKarp();
    double getTotalMaxFlow();
    double getFlowToCity(Code cityCode);
    std::map<int,double> getCitiesFlow();

    int removeReservoir(Code reservoirCode);

};


#endif //FEUP_DA_01_BASICSERVICEMETRICS_H
