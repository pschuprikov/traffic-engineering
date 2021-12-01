#pragma once


#include <omnetpp.h>

#include "inet/networklayer/contract/ipv4/Ipv4Address.h"

#include "Tunnel.h"


namespace TrafficEngineering {

void addMulticastTunnel(omnetpp::cModule *controller, const Tunnel &tunnel, inet::Ipv4Address multicastGroup);

} // namespace TrafficEngineering
