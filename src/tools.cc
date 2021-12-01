#include "tools.h"


namespace TrafficEngineering  {

namespace {

void buildSpanningTree(const Node &node, std::map<std::string, bool> &visited, Tunnel &tunnel) {
    visited[node.getName()] = true;
    for (const auto &interface : node.getInterfaces()) {
        const Link &link = node.getLink(interface);
        Node *nextNode = link.getRemoteNode();
        if (visited.count(nextNode->getName()) != 0) {
            continue;
        }
        tunnel.addLink(link);
        buildSpanningTree(*nextNode, visited, tunnel);
    }
}

} // namespace

Topology makeTopology(omnetpp::cTopology &topology) {
    Topology result;
    for (int i = 0; i < topology.getNumNodes(); i++) {
        auto *module = topology.getNode(i)->getModule();
        for (int i = 0; i < module->gateCount(); i++) {
            auto *gate = module->gateByOrdinal(i);
            if (gate->getType() == omnetpp::cGate::INPUT) {
                continue;
            }
            std::string begin = module->getName();
            std::string end = gate->getNextGate()->getOwnerModule()->getFullName();
            std::string interface = std::string(gate->getBaseName());
            interface.pop_back();
            interface += std::to_string(gate->getIndex());
            result.addLink({begin, end, interface});
        }
    }
    return result;
}

Topology makeTopologyFromCurrentNetwork(const std::vector<std::string> &nedTypeNames) {
    omnetpp::cTopology topology;
    topology.extractByNedTypeName(nedTypeNames);
    return makeTopology(topology);
}

Tunnel getRandomSpanningTree(const Topology &topology) {
    int random = rand() % topology.getNodeNumber();
    std::string randomNodeName = topology.getAllNodeNames()[random];
    return getSpanningTree(topology, randomNodeName);
}

Tunnel getSpanningTree(const Topology &topology, const std::string &rootNodeName) {
    const Node &root = topology.getNodeByName(rootNodeName);
    Tunnel tunnel(root);
    std::map<std::string, bool> visited;
    buildSpanningTree(root, visited, tunnel);
    return tunnel;
}

} // namespace TrafficEngineering
