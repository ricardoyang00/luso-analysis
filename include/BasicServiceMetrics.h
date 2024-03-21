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
    BasicServiceMetrics(Graph<Code> codeGraphCopy, const DataContainer& dataContainer);
    void edmondsKarpSpecific(const Code& source, const Code& target);
    void edmondsKarpAllCities(const Code& source);
    void printSpecific();
};


#endif //FEUP_DA_01_BASICSERVICEMETRICS_H