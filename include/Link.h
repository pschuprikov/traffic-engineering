#pragma once


#include <iostream>


namespace TrafficEngineering  {

struct Link {
    std::string localNodeName;
    std::string remoteNodeName;
    std::string localInterfaceName;
    std::string remoteInterfaceName;
    double datarate;
    double delay;
    double minDelay;
    double maxJitter;
};

} // namespace TrafficEngineering
