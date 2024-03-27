#include "BasicServiceMetrics.h"
#include <sstream>
#include <iomanip>

BasicServiceMetrics::BasicServiceMetrics(const Graph<Code>& graph, const DataContainer &container) : dataContainer(container) {
    // create a deep copy of the graph
    for (const auto& vertex : graph.getVertexSet()) {
        codeGraphCopy.addVertex(vertex->getInfo());
    }

    for (const auto& vertex : graph.getVertexSet()) {
        for (const auto& edge : vertex->getAdj()) {
            auto orig = codeGraphCopy.findVertex(edge->getOrig()->getInfo());
            auto dest = codeGraphCopy.findVertex(edge->getDest()->getInfo());
            codeGraphCopy.addEdge(orig->getInfo(), dest->getInfo(), edge->getWeight());
        }
    }
}

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
            if (destCode.getType() == CodeType::CITY)
                flow += e->getFlow();
        }
    }
    return flow / 2; // super sink not considered, only for algorithm
}

void BasicServiceMetrics::printHeader() {
   std::cout << std::left << std::setw(20) << "Name" << "|    ";
   std::cout << std::setw(8) << "Code" << "|    ";
   std::cout << std::setw(10) << "Max Flow" << std::endl;

   std::cout << std::setfill('-') << std::setw(20) << "" << "|";
   std::cout << std::setw(12) << "" << "|";
   std::cout << std::setw(14) << "" << std::setfill(' ') << std::endl;
}

void BasicServiceMetrics::printCityMaxFlow(const std::string& name, const std::string& code, const double& maxFlow) {
   int nameWidth = (name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != std::string::npos) ? 21 : 20;
   std::cout << std::setw(nameWidth) << name << "|    ";
   std::cout << std::setw(8) << code << "|    ";
   std::cout << std::setw(10) << maxFlow << std::endl;
}

void BasicServiceMetrics::printEachCityMaxFlow() {
    Vertex<Code>* superSink = codeGraphCopy.findVertex(Code("C_0"));
    if (superSink == nullptr) {
        throw std::logic_error("Couldn't find super sink C_0");
    }

    auto cTable = dataContainer.getCityHashTable();
    printHeader();

    for (const auto& edge : superSink->getIncoming()) {
        auto cityVertex = edge->getOrig()->getInfo();
        auto c = cTable.find(cityVertex.getNumber())->second;

        printCityMaxFlow(c.getName(), cityVertex.getCompleteCode(), edge->getFlow());
    }
}

void BasicServiceMetrics::printSpecificCityMaxFlow(const Code& city) {
    Vertex<Code>* superSink = codeGraphCopy.findVertex(Code("C_0"));
    if (superSink == nullptr) {
        throw std::logic_error("Couldn't find super sink C_0");
    }

    auto cTable = dataContainer.getCityHashTable();
    printHeader();

    for (const auto& edge : superSink->getIncoming()) {
        auto cityVertex = edge->getOrig()->getInfo();
        if (cityVertex == city) {
            auto c = cTable.find(cityVertex.getNumber())->second;
            printCityMaxFlow(c.getName(), cityVertex.getCompleteCode(), edge->getFlow());
            return;
        }
    }
    throw std::logic_error("Invalid city chosen");
}