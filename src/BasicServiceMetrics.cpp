#include "BasicServiceMetrics.h"
#include <sstream>

BasicServiceMetrics::BasicServiceMetrics(Graph<Code> graph, const DataContainer &container) : codeGraphCopy(graph), dataContainer(container) {}

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
    addSuperSource();
    addSuperSink();

    Vertex<Code>* s = codeGraphCopy.findVertex(Code("R_0"));
    Vertex<Code>* t = codeGraphCopy.findVertex(Code("C_0"));

    if (s == nullptr || t == nullptr || s == t) {
        throw std::logic_error("Invalid source and/or target vertex");
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


/*void BasicServiceMetrics::edmondsKarpSpecific(const Code& source, const Code& target) {
    if (source.getType() != CodeType::RESERVOIR) {
        throw std::logic_error("Invalid source, please set water reservoir as source, i.e. R_5");
    }
    if (target.getType() != CodeType::CITY) {
        throw std::logic_error("Invalid source, please set city as target, i.e. C_5");
    }

    Vertex<Code>* s = codeGraphCopy.findVertex(source);
    Vertex<Code>* t = codeGraphCopy.findVertex(target);

    if (s == nullptr || t == nullptr || s == t) {
        throw std::logic_error("Invalid source and/or target vertex");
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
}*/

void BasicServiceMetrics::edmondsKarpAllCities(const Code &source) {
    if (source.getType() != CodeType::RESERVOIR) {
        throw std::logic_error("Invalid source, please set water reservoir as source, i.e. R_5");
    }

    Vertex<Code>* s = codeGraphCopy.findVertex(source);

    if (s == nullptr) {
        throw std::logic_error("Invalid source vertex");
    }

    for (auto v : codeGraphCopy.getVertexSet()) {
        for (auto& e : v->getAdj()) {
            e->setFlow(0);
        }
    }

    for (auto t : codeGraphCopy.getVertexSet()) {
        if (t->getInfo().getType() == CodeType::CITY) {
            while (findAugmentingPath(s, t)) {
                double bnValue = findBottleNeckValue(s, t);
                augmentFlowAlongPath(s, t, bnValue);
            }
        }
    }
}

void BasicServiceMetrics::printSpecific() {
    std::stringstream ss;
    for(auto v : codeGraphCopy.getVertexSet()) {
        ss.str("");
        bool hasContent = false;
        for (const auto e : v->getAdj())
            if (e->getFlow() != 0) {
                ss << e->getDest()->getInfo().getCompleteCode() << "[Flow: " << e->getFlow() << "]";
                hasContent = true;
            } else continue;
        ss << ")";
        if (hasContent) std::cout << v->getInfo().getCompleteCode() << "->(" << ss.str() << std::endl;
    }
}

double BasicServiceMetrics::getMaxFlow() {
    double flow = 0;
    for (auto v : codeGraphCopy.getVertexSet()) {
        for (const auto e : v->getAdj()) {
            auto destCode = e->getDest()->getInfo();
            if (destCode.getType() == CodeType::CITY)
                flow += e->getFlow();
        }
    }
    return flow / 2; // not considering super sink
}