#include "algorithms.h"

#include <unordered_set>
#include <unordered_map>
#include <map>
#include <limits>

#include "algorithmModels.h"


namespace TrafficEngineering {

namespace {

Tunnel treeToTunnel(const Topology &topology, const Tree &tree) {
    auto &root = topology.getNodeByName(tree.getRoot());
    Tunnel result(root);
    for (const auto &edge : tree.getEdgesDFSOrder()) {
        const auto &link = topology.getLink(edge.from, edge.to);
        result.addLink(link);
    }
    return result;
}

AdjustmentResult dfs(const Node &node, const Tunnel &tunnel,
                     const std::map<std::pair<std::string, std::string>, double> &maxTime) {
    AdjustmentResult result;
    result.minDelay = std::numeric_limits<double>::max();
    result.maxDelay = 0;
    result.maxPeriod = 0;
    if (node.getInterfaceNumber() == 0) {
        result.minDelay = 0;
        result.maxDelay = 0;
        result.maxPeriod = 0;
        return result;
    }
    for (const auto &link : node.getAllLinks()) {
        auto neighbour = tunnel.getNode(link.remoteNodeName);
        auto neighbourResult = dfs(neighbour, tunnel, maxTime);
        auto transferTime = tunnel.getLoadSize() / link.datarate;
        auto sumTransferTime = maxTime.at({link.localNodeName, link.remoteNodeName});
        result.minDelay = std::min(result.minDelay, neighbourResult.minDelay + transferTime + link.minDelay);
        result.maxDelay = std::max(result.maxDelay, neighbourResult.maxDelay + sumTransferTime + link.minDelay + link.maxJitter);
        result.maxPeriod = std::max(result.maxPeriod, sumTransferTime + std::max(transferTime, neighbourResult.maxPeriod + link.maxJitter));
    }
    return result;
}

} // namespace

std::vector<AdjustmentResult> adjustment(std::vector<Tunnel> &tunnels) {
    std::map<std::pair<std::string, std::string>, double> maxTime;
    for (const auto &tunnel : tunnels) {
        for (const auto &link : tunnel.getAllLinks()) {
            std::pair<std::string, std::string> key = {link.localNodeName, link.remoteNodeName};
            if (maxTime.count(key) != 0) {
                maxTime[key] += 96 / link.datarate;  // interpacket gap
            }
            maxTime[key] += tunnel.getLoadSize() / link.datarate;
        }
    }

    std::vector<AdjustmentResult> results;
    for (auto &tunnel : tunnels) {
        auto result = dfs(tunnel.getRoot(), tunnel, maxTime);
        // tunnel.setPeriodValue(std::max(result.maxPeriod, tunnel.getPeriod()));
        results.push_back(result);
    }
    return results;
}

Tunnel optimization(const Topology &topology, std::vector<Tunnel> &tunnels, const AppDescription &app) {
    std::map<std::pair<std::string, std::string>, double> weights;
    for (const auto &link : topology.getAllLinks()) {
        weights[{link.localNodeName, link.remoteNodeName}] = 1.0 * (app.messageLength + 54) / link.datarate + link.minDelay + link.maxJitter;
    }
    for (const auto &tunnel : tunnels) {
        for (const auto &link : tunnel.getAllLinks()) {
            weights[{link.localNodeName, link.remoteNodeName}] += tunnel.getLoadSize() / link.datarate;
            weights[{link.localNodeName, link.remoteNodeName}] += 96 / link.datarate;  // interpacket gap
        }
    }

    std::vector<Edge> edges;
    for (const auto &entry : weights) {
        Edge edge = {entry.first.first, entry.first.second, entry.second};
        edges.push_back(edge);
    }

    Graph graph(topology.getNodeNumber(), edges);

    Tree tree(app.appOwnerName);
    std::unordered_set<std::string> receivers(app.appReceiverNames.begin(), app.appReceiverNames.end());
    while (!receivers.empty()) {
        std::string bestReceiver;
        double bestBranchWeight = 0;
        std::vector<Edge> bestBranch;
        for (const auto &receiver : receivers) {
            double bestDistanceToTree = std::numeric_limits<double>::max();
            std::vector<Edge> bestPathToTree;
            for (const auto &node : tree.getAllNodes()) {
                double theShortestPathWeight = graph.theShortestPathWeight(node, receiver);
                double theLongestPathWeight = tree.theLongestPathWeight(node);
                double currentDistance = theShortestPathWeight + std::max(0.0, theShortestPathWeight - theLongestPathWeight);
                if (bestDistanceToTree > currentDistance) {
                    bestDistanceToTree = currentDistance;
                    bestPathToTree = graph.theShortestPath(node, receiver);
                }
            }
            if (bestBranchWeight < bestDistanceToTree) {
                bestReceiver = receiver;
                bestBranchWeight = bestDistanceToTree;
                bestBranch = bestPathToTree;
            }
        }
        tree.addBranch(bestBranch);
        receivers.erase(bestReceiver);
    }

    Tunnel tunnel = treeToTunnel(topology, tree);
    tunnel.setLoadSize(app.messageLength);

    return tunnel;
}

} // namespace TrafficEngineering
