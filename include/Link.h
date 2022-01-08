#pragma once


#include <iostream>


namespace TrafficEngineering  {

struct Link {
    std::string localNodeName;
    std::string remoteNodeName;
    std::string localInterfaceName;
    std::string remoteInterfaceName;
    double datarate;
};

} // namespace TrafficEngineering
