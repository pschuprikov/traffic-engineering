#pragma once

#include <vector>

#include "applications.h"
#include "Tunnel.h"
#include "Topology.h"


namespace TrafficEngineering {

Tunnel optimization(const Topology &topology, const std::vector<Tunnel> &tunnels, const AppDescription &app);

} // namespace TrafficEngineering
