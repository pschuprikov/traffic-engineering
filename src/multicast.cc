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

void addMulticastTunnel(omnetpp::cModule *controller, const Tunnel &tunnel, inet::Ipv4Address multicastGroup) {
    for (const auto *node : tunnel.getDFSOrder()) {
        auto *module = controller->getModuleByPath(node->getName().c_str());
        auto *routingTable = inet::L3AddressResolver().getIpv4RoutingTableOf(module);
        auto *interfaceTable = inet::L3AddressResolver().interfaceTableOf(module);
        auto *route = new inet::Ipv4MulticastRoute();
        route->setMulticastGroup(multicastGroup);
        for (const auto &interfaceName : node->getInterfaces()) {
            auto *interface = new inet::IMulticastRoute::OutInterface(interfaceTable->findInterfaceByName(interfaceName.c_str()));
            route->addOutInterface(interface);
        }
        routingTable->addMulticastRoute(route);
    }
}

} // namespace TrafficEngineering
