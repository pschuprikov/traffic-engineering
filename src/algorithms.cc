#include "algorithms.h"

#include <unordered_set>
#include <unordered_map>
#include <map>
#include <limits>

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

    std::cout << "Sender: " << app.appOwnerName << '\n';
    for (const auto &receiver : app.appReceiverNames) {
        std::cout << receiver << ' ';
    }
    std::cout << '\n';

    Tree tree(app.appOwnerName);
    std::unordered_set<std::string> receivers(app.appReceiverNames.begin(), app.appReceiverNames.end());
    while (!receivers.empty()) {
        std::string bestReceiver;
        double branchWeight = 0;
        std::vector<Edge> branch;
        for (const auto &receiver : receivers) {
            for (const auto &node : tree.getAllNodes()) {
                double theShortestPathWeight = graph.theShortestPathWeight(node, receiver);
                double theLongestPathWeight = tree.theLongestPathWeight(node);
                double currentWeight = theShortestPathWeight + std::max(0.0, theShortestPathWeight - theLongestPathWeight);
                if (branchWeight < currentWeight) {
                    bestReceiver = receiver;
                    branchWeight = currentWeight;
                    branch = graph.theShortestPath(node, receiver);
                }
            }
        }
        tree.addBranch(branch);
        receivers.erase(bestReceiver);
    }
}

} // namespace TrafficEngineering
