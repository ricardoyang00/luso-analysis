#include "BasicServiceMetrics.h"

using namespace std;

BasicServiceMetrics::BasicServiceMetrics(const Graph<Code>& graph, const DataContainer &container) : originalCodeGraph(graph), dataContainer(container) {
    resetBSMGraph();
}

void BasicServiceMetrics::resetBSMGraph() {
    this->codeGraphCopy = deepGraphCopy(originalCodeGraph);
    edmondsKarp();
}

Graph<Code>& BasicServiceMetrics::getBSMGraph() { return codeGraphCopy; }

void BasicServiceMetrics::testAndVisit(queue<Vertex<Code> *> &q, Edge<Code> *e, Vertex<Code> *w, double residual) {
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

    queue<Vertex<Code>*> q;
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
            bnValue = min(bnValue, edge->getWeight() - edge->getFlow());
            current = edge->getOrig();
        } else {
            bnValue = min(bnValue, edge->getFlow());
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

void BasicServiceMetrics::edmondsKarp() {
    Vertex<Code>* s = codeGraphCopy.findVertex(Code("R_0"));
    Vertex<Code>* t = codeGraphCopy.findVertex(Code("C_0"));

    if (s == nullptr || t == nullptr) {
        throw logic_error("Couldn't find super source/sink (function edmondsKarp)");
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
            if (destCode.getType() == CodeType::CITY && destCode.getNumber() == 0)
                flow += e->getFlow();
        }
    }
    return flow;
}

double BasicServiceMetrics::getFlowToCity(const Code& cityCode) {
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

void BasicServiceMetrics::removeReservoir(const Code& reservoirCode) {
    auto reservoir = codeGraphCopy.findVertex(reservoirCode);
    if (reservoir == nullptr) {
        cout << "Error: Couldn't find " << reservoirCode.getCompleteCode() << endl;
        return;
    }

    codeGraphCopy.removeVertex(reservoirCode);

    edmondsKarp();
}

void BasicServiceMetrics::removePumpingStation(const Code& stationCode) {
    auto reservoir = codeGraphCopy.findVertex(stationCode);
    if (reservoir == nullptr) {
        cout << "Error: Couldn't find " << stationCode.getCompleteCode() << endl;
        return;
    }

    codeGraphCopy.removeVertex(stationCode);

    edmondsKarp();
}

void BasicServiceMetrics::removePipes(vector<pair<Code,Code>> pipeCodes) {
    for (auto pair : pipeCodes) {
        auto sourcePipe = codeGraphCopy.findVertex(pair.first);
        auto targetPipe = codeGraphCopy.findVertex(pair.second);
        if (sourcePipe == nullptr) {
            cout << "Error: Couldn't find " << pair.first.getCompleteCode() << endl;
            continue;
        }
        if (targetPipe == nullptr) {
            cout << "Error: Coudln't find " << pair.second.getCompleteCode() << endl;
            continue;
        }

        codeGraphCopy.removeEdge(pair.first,pair.second);
        codeGraphCopy.removeEdge(pair.second,pair.first);
    }

    edmondsKarp();
}

map<int,double> BasicServiceMetrics::getCitiesFlow() {
    map<int,double> citiesFlow; //first city code number , second city's flow

    for (const auto& pair : dataContainer.getCityHashTable()) {
        auto cityCode = pair.second.getCode();
        double cityFlow = getFlowToCity(cityCode);

        citiesFlow[cityCode.getNumber()] = cityFlow;
    }

    return citiesFlow;
}

void BasicServiceMetrics::removeExtraBidirectionalPipes() {
    for (const auto& v : codeGraphCopy.getVertexSet()) {
        for (auto& e : v->getAdj()) {
            if (e->getReverse() != nullptr && e->getFlow() != 0 && e->getReverse()->getFlow() == 0) {
                codeGraphCopy.removeEdge(e->getDest()->getInfo(), e->getOrig()->getInfo());
            }
        }
    }
}

void BasicServiceMetrics::pumpRemainingWaterFromReservoirs() {
    for (const auto& v : codeGraphCopy.getVertexSet()) {
        if (v->getInfo().getType() == CodeType::RESERVOIR && v->getInfo().getNumber() != 0) {
            auto rTable = dataContainer.getReservoirHashTable();
            auto r = rTable.find(v->getInfo().getNumber())->second;

            double maxDelivery = r.getMaxDelivery();
            double currentDelivery = 0;

            for (const auto& e : v->getAdj()) {
                currentDelivery += e->getFlow();
            }

            double remainingDelivery = maxDelivery - currentDelivery;
            for (auto& e : v->getAdj()) {
                double availableFlow = e->getWeight() - e->getFlow();
                if (availableFlow <= 0) continue; // No available flow on this edge
                double flowToAdd = std::min(remainingDelivery, availableFlow);
                e->setFlow(e->getFlow() + flowToAdd);
                remainingDelivery -= flowToAdd;
                if (remainingDelivery <= 0) break; // No more delivery needed
            }
        }
    }
}

void BasicServiceMetrics::balanceFlow() {
    map<int, double> citiesFlow = getCitiesFlow();

    priority_queue<pair<double, Edge<Code>*>, vector<pair<double, Edge<Code>*>>, greater<>> pq;

    removeExtraBidirectionalPipes();
    pumpRemainingWaterFromReservoirs();

    for (const auto& v : codeGraphCopy.getVertexSet()) {
        if (v->getInfo().getNumber() != 0) {
            for (const auto& e : v->getAdj()) {
                double remainingCap = e->getWeight() - e->getFlow();
                pq.emplace(remainingCap, e);
            }
        }
    }

    while (!pq.empty()) {
        auto [remainingCap, edge] = pq.top();
        pq.pop();

        auto orig = edge->getOrig();
        auto dest = edge->getDest();

        for (auto adjEdge : orig->getAdj()) {
            double adjRemCap = adjEdge->getWeight() - adjEdge->getFlow();
            if (adjRemCap == 0) continue;

            double transfer = min(remainingCap, adjRemCap);
            edge->setFlow(edge->getFlow() + transfer);
            adjEdge->setFlow(adjEdge->getFlow() - transfer);
        }
    }
}