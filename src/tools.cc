#include "tools.h"


namespace TrafficEngineering  {

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
            std::string interface = gate->getBaseName() + std::to_string(gate->getIndex());
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

} // namespace TrafficEngineering
