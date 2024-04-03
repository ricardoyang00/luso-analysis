#include "BasicServiceMetrics.h"
#include <sstream>
#include <iomanip>

using namespace std;

BasicServiceMetrics::BasicServiceMetrics(const Graph<Code>& graph, const DataContainer &container) : originalCodeGraph(graph), dataContainer(container) {
    resetBSMGraph();
}

void BasicServiceMetrics::resetBSMGraph() {
    // create a deep copy of the graph
    for (const auto& vertex : originalCodeGraph.getVertexSet()) {
        codeGraphCopy.addVertex(vertex->getInfo());
    }
    for (const auto& vertex : originalCodeGraph.getVertexSet()) {
        for (const auto& edge : vertex->getAdj()) {
            auto orig = codeGraphCopy.findVertex(edge->getOrig()->getInfo());
            auto dest = codeGraphCopy.findVertex(edge->getDest()->getInfo());
            codeGraphCopy.addEdge(orig->getInfo(), dest->getInfo(), edge->getWeight());
        }
    }

    addSuperSource();
    addSuperSink();
}

Graph<Code>& BasicServiceMetrics::getBSMGraph() { return codeGraphCopy; }

void BasicServiceMetrics::testAndVisit(std::queue<Vertex<Code> *> &q, Edge<Code> *e, Vertex<Code> *w, double residual) {
    if (!w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

bool BasicServiceMetrics::findAugmentingPath(Vertex<Code> *s, Vertex<Code> *t) {
    for (auto v : codeGraphCopy.getVertexSet()) {
        v->setVisited(false);
        v->setPath(nullptr);
    }

    std::queue<Vertex<Code>*> q;
    q.push(s);
    s->setVisited(true);

    while (!q.empty() && !t->isVisited()) {
        auto current = q.front();
        q.pop();

        for (auto edge : current->getAdj()) {
            testAndVisit(q, edge, edge->getDest(), edge->getWeight() - edge->getFlow());
        }

        for (auto edge : current->getIncoming()) {
            testAndVisit(q, edge, edge->getOrig(), edge->getFlow());
        }
    }

    return t->isVisited();
}

double BasicServiceMetrics::findBottleNeckValue(Vertex<Code> *s, Vertex<Code> *t) {
    double bnValue = INF;
    auto current = t;

    while (current != s) {
        auto edge = current->getPath();

        if (edge->getDest() == current) {
            bnValue = std::min(bnValue, edge->getWeight() - edge->getFlow());
            current = edge->getOrig();
        } else {
            bnValue = std::min(bnValue, edge->getFlow());
            current = edge->getDest();
        }
    }

    return bnValue;
}

void BasicServiceMetrics::augmentFlowAlongPath(Vertex<Code> *s, Vertex<Code> *t, double bnValue) {
    auto current = t;

    while (current != s) {
        auto edge = current->getPath();
        double flow = edge->getFlow();
        if (edge->getDest() == current) {
            edge->setFlow(flow + bnValue);
            current = edge->getOrig();
        } else {
            edge->setFlow(flow - bnValue);
            current = edge->getDest();
        }
    }
}

void BasicServiceMetrics::addSuperSource() {
    codeGraphCopy.addVertex(Code("R_0"));
    auto superSource = codeGraphCopy.findVertex(Code("R_0"));
    if (superSource == nullptr) {
        throw std::logic_error("Super source R_0 not found in graph");
    }
    auto rTable = dataContainer.getReservoirHashTable();
    for (auto reservoir : codeGraphCopy.getVertexSet()) {
        if (reservoir->getInfo().getType() == CodeType::RESERVOIR && reservoir != superSource) {
            auto r = rTable.find(reservoir->getInfo().getNumber())->second;
            codeGraphCopy.addEdge(superSource->getInfo(), reservoir->getInfo(), r.getMaxDelivery());
        }
    }
}

void BasicServiceMetrics::addSuperSink() {
    codeGraphCopy.addVertex(Code("C_0"));
    auto superSink = codeGraphCopy.findVertex(Code("C_0"));
    if (superSink == nullptr) {
        throw std::logic_error("Super sink C_0 not found in graph");
    }
    auto cTable = dataContainer.getCityHashTable();
    for (auto city : codeGraphCopy.getVertexSet()) {
        if (city->getInfo().getType() == CodeType::CITY && city != superSink) {
            auto c = cTable.find(city->getInfo().getNumber())->second;
            codeGraphCopy.addEdge(city->getInfo(), superSink->getInfo(), c.getDemand());
        }
    }
}

void BasicServiceMetrics::edmondsKarp() {
    Vertex<Code>* s = codeGraphCopy.findVertex(Code("R_0"));
    Vertex<Code>* t = codeGraphCopy.findVertex(Code("C_0"));

    if (s == nullptr || t == nullptr) {
        throw std::logic_error("Couldn't find super source/sink");
    }

    for (auto v : codeGraphCopy.getVertexSet()) {
        for (auto& e : v->getAdj()) {
            e->setFlow(0);
        }
    }

    while (findAugmentingPath(s, t)) {
        double bnValue = findBottleNeckValue(s, t);
        augmentFlowAlongPath(s, t, bnValue);
    }
}

double BasicServiceMetrics::getTotalMaxFlow() {
    double flow = 0;
    for (auto v : codeGraphCopy.getVertexSet()) {
        for (const auto e : v->getAdj()) {
            auto destCode = e->getDest()->getInfo();
            //if (destCode.getType() == CodeType::CITY)
            if (destCode.getType() == CodeType::CITY && destCode.getNumber() == 0)
                flow += e->getFlow();
        }
    }
    //return flow / 2; // super sink not considered, only for algorithm
    return flow;
}

double BasicServiceMetrics::getFlowToCity(Code cityCode) {
    double flow = 0;
    auto v = codeGraphCopy.findVertex(cityCode);
    for (auto e : v->getIncoming()) {
        auto destCode = e->getDest()->getInfo();
        if (destCode.getType() == cityCode.getType() && destCode.getNumber() == cityCode.getNumber()) {
            flow += e->getFlow();
        }
    }
    return flow;
}

int BasicServiceMetrics::removeReservoir(Code reservoirCode) {
    auto reservoir = codeGraphCopy.findVertex(reservoirCode);
    if (reservoir == nullptr) return 1;

    codeGraphCopy.removeVertex(reservoirCode);

    edmondsKarp();
    return 0;
}

map<int,double> BasicServiceMetrics::getCitiesFlow() {
    map<int,double> citiesFlow; //first city code number , second city's flow

    for (auto pair : dataContainer.getCityHashTable()) {
        auto cityCode = pair.second.getCode();
        double cityFlow = getFlowToCity(cityCode);

        citiesFlow[cityCode.getNumber()] = cityFlow;
    }

    return citiesFlow;
}