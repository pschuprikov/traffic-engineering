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
                     const std::map<std::pair<std::string, std::string>, double> &sumTime) {
    AdjustmentResult result;
    result.minDelay = std::numeric_limits<double>::max();
    result.maxDelay = 0;
    if (node.getInterfaceNumber() == 0) {
        result.minDelay = 0;
        result.maxDelay = 0;
        return result;
    }
    for (const auto &link : node.getAllLinks()) {
        auto neighbour = tunnel.getNode(link.remoteNodeName);
        auto neighbourResult = dfs(neighbour, tunnel, sumTime);
        auto transferTime = tunnel.getLoadSize() / link.datarate;
        auto sumTransferTime = sumTime.at({link.localNodeName, link.remoteNodeName});
        result.minDelay = std::min(result.minDelay, neighbourResult.minDelay + link.delay + sumTransferTime);
        result.maxDelay = std::max(result.maxDelay, neighbourResult.maxDelay + link.delay + transferTime);
    }
    return result;
}

} // namespace

std::vector<AdjustmentResult> adjustment(const std::vector<Tunnel> &tunnels) {
    std::map<std::pair<std::string, std::string>, double> sumTime;
    for (const auto &tunnel : tunnels) {
        for (const auto &link : tunnel.getAllLinks()) {
            std::pair<std::string, std::string> key = {link.localNodeName, link.remoteNodeName};
            sumTime[key] += tunnel.getLoadSize() / link.datarate;
        }
    }

    std::vector<AdjustmentResult> result;
    for (const auto &tunnel : tunnels) {
        result.push_back(dfs(tunnel.getRoot(), tunnel, sumTime));
    }
    return result;
}

Tunnel optimization(const Topology &topology, const std::vector<Tunnel> &tunnels, const AppDescription &app) {
    std::map<std::pair<std::string, std::string>, double> weights;
    for (const auto &link : topology.getAllLinks()) {
        weights[{link.localNodeName, link.remoteNodeName}] = 1.0 * app.messageLength / link.datarate + link.delay;
    }
    for (const auto &tunnel : tunnels) {
        for (const auto &link : tunnel.getAllLinks()) {
            weights[{link.localNodeName, link.remoteNodeName}] += tunnel.getLoadSize() / link.datarate;
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
    tunnel.setPeriod(app.sendInterval);

    return tunnel;
}

} // namespace TrafficEngineering
