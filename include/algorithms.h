#pragma once

#include <vector>

#include "applications.h"
#include "Tunnel.h"
#include "Topology.h"


namespace TrafficEngineering {

struct AdjustmentResult {
    double minDelay;
    double maxDelay;
};

std::vector<AdjustmentResult> adjustment(const std::vector<Tunnel> &tunnels);

Tunnel optimization(const Topology &topology, const std::vector<Tunnel> &tunnels, const AppDescription &app);

} // namespace TrafficEngineering
