#pragma once

#include <vector>

#include "applications.h"
#include "Tunnel.h"
#include "Topology.h"


namespace TrafficEngineering {

struct AdjustmentResult {
    double minDelay;
    double maxDelay;
    double maxPeriod;
};

std::vector<AdjustmentResult> adjustment(std::vector<Tunnel> &tunnels);

Tunnel optimization(const Topology &topology, std::vector<Tunnel> &tunnels, const AppDescription &app);

} // namespace TrafficEngineering
