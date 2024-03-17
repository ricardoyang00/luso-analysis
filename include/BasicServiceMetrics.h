#ifndef FEUP_DA_01_BASICSERVICEMETRICS_H
#define FEUP_DA_01_BASICSERVICEMETRICS_H

#include "ParseData.h"

class BasicServiceMetrics {
private:
    const Graph<Code>& codeGraph;
    const DataContainer& dataContainer;
    void testAndVisit(std::queue<Vertex<Code>*>& q, Edge<Code>* e, Vertex<Code>* w, double residual);
    bool findAugmentingPath(Vertex<Code>* s, Vertex<Code>* t);
    double findBottleNeckValue(Vertex<Code>* s, Vertex<Code>* t);
    void augmentFlowAlongPath(Vertex<Code>* s, Vertex<Code>* t, double bnValue);
public:
    BasicServiceMetrics(const Graph<Code>& codeGraph, const DataContainer& dataContainer);
    void edmondsKarp(const Code& source, const Code& target);
};


#endif //FEUP_DA_01_BASICSERVICEMETRICS_H
