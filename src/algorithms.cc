#include "algorithms.h"

#include <map>

#include "algorithmModels.h"


namespace TrafficEngineering {

void optimization(const Topology &topology, const std::vector<Tunnel> &tunnels, const AppDescription &app) {
    std::map<std::pair<std::string, std::string>, double> weights;
    for (const auto &link : topology.getAllLinks()) {
        weights[{link.localNodeName, link.remoteNodeName}] = 1.0 * app.messageLength / link.datarate;
    }
    for (const auto &tunnel : tunnels) {
        for (const auto &link : tunnel.getAllLinks()) {
            weights[{link.localNodeName, link.remoteNodeName}] += 1.0 * tunnel.getLoadSize() / link.datarate;
        }
    }

    std::vector<Edge> edges;
    for (const auto &entry : weights) {
        Edge edge = {entry.first.first, entry.first.second, entry.second};
        edges.push_back(edge);
    }

    Graph graph(topology.getNodeNumber(), edges);
}

} // namespace TrafficEngineering
