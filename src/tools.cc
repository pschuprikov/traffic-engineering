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
    EV_STATICCONTEXT;
    Topology result;
    for (int i = 0; i < topology.getNumNodes(); i++) {
        auto *module = topology.getNode(i)->getModule();
        for (int i = 0; i < module->gateCount(); i++) {
            auto const localGate = module->gateByOrdinal(i);
            if (localGate->getType() == omnetpp::cGate::INPUT) {
                continue;
            }

            omnetpp::cGate * remoteGate = localGate->getNextGate(); 
            while (remoteGate && topology.getNodeFor(remoteGate->getOwnerModule()) == nullptr) {
                remoteGate = remoteGate->getNextGate();
            }
            if (remoteGate == nullptr) {
                throw std::logic_error(std::string("couldn't find a peer of ") + localGate->getName());
            }

            auto const remoteModule = remoteGate->getOwnerModule();
            Link link;
            link.localNodeName = module->getFullPath();
            link.remoteNodeName = remoteModule->getFullPath();
            link.localInterfaceName = getGateName(localGate);
            link.remoteInterfaceName = getGateName(remoteGate);
            link.datarate = localGate->getTransmissionChannel()->par("datarate").doubleValue();
            link.delay = localGate->getTransmissionChannel()->par("delay").doubleValue();
            EV_INFO << " adding link from " << link.localNodeName << " to " << link.remoteNodeName << std::endl;
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
