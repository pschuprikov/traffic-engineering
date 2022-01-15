#include "tools.h"


namespace TrafficEngineering  {

namespace {

void buildSpanningTree(const Topology &topology, const Node &node, std::map<std::string, bool> &visited, Tunnel &tunnel) {
    visited[node.getName()] = true;
    for (const auto &interface : node.getInterfaces()) {
        const Link &link = node.getLinkByInterfaceName(interface);
        Node nextNode = topology.getNodeByName(link.remoteNodeName);
        if (visited.count(nextNode.getName()) != 0) {
            continue;
        }
        tunnel.addLink(link);
        buildSpanningTree(topology, nextNode, visited, tunnel);
    }
}

std::string getGateName(omnetpp::cGate *gate) {
    std::string result = std::string(gate->getBaseName());
    result.pop_back();
    result += std::to_string(gate->getIndex());
    return result;
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
            Link link;
            link.localNodeName = module->getName();
            link.remoteNodeName = gate->getNextGate()->getOwnerModule()->getFullName();
            link.localInterfaceName = getGateName(gate);
            link.remoteInterfaceName = getGateName(gate->getNextGate());

            omnetpp::cChannel *channel = gate->getTransmissionChannel();
            std::string type = channel->getNedTypeName();
            if (type == "FatTreeNetwork.SwitchEthernet") {
                link.minDelay = 0.000002;
                link.maxJitter = 0.000001;
            } else if (type == "FatTreeNetwork.ServerEthernet") {
                link.minDelay = 0.000005;
                link.maxJitter = 0.000005;
            }
            link.datarate = channel->par("datarate").doubleValue();
            link.delay = channel->par("delay").doubleValue();

            result.addLink(link);
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
    buildSpanningTree(topology, root, visited, tunnel);
    return tunnel;
}

std::vector<std::string> getSourceFromCurrentNetwork(const std::vector<std::string> &nedSourceTypes) {
    std::vector<std::string> result;
    omnetpp::cTopology topology;
    topology.extractByNedTypeName(nedSourceTypes);
    for (int i = 0; i < topology.getNumNodes(); i++) {
        auto *module = topology.getNode(i)->getModule();
        std::string nedType(module->getNedTypeName());
        for (const auto &sourceType : nedSourceTypes) {
            if (nedType == sourceType) {
                result.push_back(std::string(module->getName()));
            }
        }
    }
    return result;
}

} // namespace TrafficEngineering
