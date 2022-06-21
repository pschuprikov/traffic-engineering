#include "multicast.h"

#include "tools.h"

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
    EV_STATICCONTEXT;
    EV_INFO << "adding multicast tunnel from " << tunnel.getRootName() << std::endl;
    auto const rootIFaceTable = inet::L3AddressResolver().interfaceTableOf(controller->getModuleByPath(tunnel.getRootName().c_str()));
    auto const rootIface = rootIFaceTable->findFirstNonLoopbackInterface();

    for (const auto &node : tunnel.getDFSOrder()) {
        auto *module = controller->getModuleByPath(node.getName().c_str());
        EV_INFO << " adding routes at " << module->getFullPath() << std::endl;
        auto *routingTable = inet::L3AddressResolver().getIpv4RoutingTableOf(module);
        if (routingTable == nullptr) {
            throw std::invalid_argument("node " + node.getName() + " doesn't have a routing table");
        }
        auto *route = new inet::Ipv4MulticastRoute();
        route->setMulticastGroup(multicastGroup);
        route->setOrigin(rootIface->getIpv4Address());
        route->setOriginNetmask(inet::Ipv4Address::ALLONES_ADDRESS);

        if (node.getName() != tunnel.getRootName()) {
            const std::string &inInterfaceName = tunnel.getInInterface(node.getName());
            auto const ifaceEntry =  getInterfaceFromModule(module, inInterfaceName);
            if (ifaceEntry == nullptr) {
                throw std::invalid_argument("couldn't find interface " + inInterfaceName + " inside " + module->getFullPath());
            }
            auto *inInterface = new inet::IMulticastRoute::InInterface(ifaceEntry);
            route->setInInterface(inInterface);
        }

        for (const auto &interfaceName : node.getInterfaces()) {
            auto const ifaceEntry = getInterfaceFromModule(module, interfaceName);
            if (ifaceEntry == nullptr) {
                throw std::invalid_argument("couldn't find interface " + interfaceName + " inside " + module->getFullPath());
            }
            auto *outInterface = new inet::IMulticastRoute::OutInterface(ifaceEntry);
            route->addOutInterface(outInterface);
        }
        routingTable->addMulticastRoute(route);
    }
}

void addMulticastGroup(omnetpp::cModule *controller, const Tunnel &tunnel, const std::string &multicastGroup) {
    addMulticastTunnel(controller, tunnel, inet::Ipv4Address(multicastGroup.c_str()));
}

} // namespace TrafficEngineering
