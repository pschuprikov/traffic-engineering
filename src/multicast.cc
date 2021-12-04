#include "multicast.h"

#include "inet/common/INETUtils.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/XMLUtils.h"
#include "inet/common/stlutils.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/networklayer/ipv4/IIpv4RoutingTable.h"
#include "inet/networklayer/contract/IRoutingTable.h"
#include "inet/networklayer/contract/ipv4/Ipv4Address.h"


namespace TrafficEngineering {

namespace {

inet::InterfaceEntry *getInterfaceFromModule(omnetpp::cModule *module, const std::string &interfaceName) {
    auto *interfaceTable = inet::L3AddressResolver().interfaceTableOf(module);
    return interfaceTable->findInterfaceByName(interfaceName.c_str());
}

} // namespace

void addMulticastTunnel(omnetpp::cModule *controller, const Tunnel &tunnel, inet::Ipv4Address multicastGroup) {
    for (const auto *node : tunnel.getDFSOrder()) {
        auto *module = controller->getModuleByPath(node->getName().c_str());
        auto *routingTable = inet::L3AddressResolver().getIpv4RoutingTableOf(module);
        auto *route = new inet::Ipv4MulticastRoute();
        route->setMulticastGroup(multicastGroup);

        if (node->getName() != tunnel.getRootName()) {
            const std::string &inInterfaceName = tunnel.getInInterface(node->getName());
            auto *inInterface = new inet::IMulticastRoute::InInterface(getInterfaceFromModule(module, inInterfaceName));
            route->setInInterface(inInterface);
        }

        for (const auto &interfaceName : node->getInterfaces()) {
            auto *outInterface = new inet::IMulticastRoute::OutInterface(getInterfaceFromModule(module, interfaceName));
            route->addOutInterface(outInterface);
        }
        routingTable->addMulticastRoute(route);
    }
}

} // namespace TrafficEngineering
