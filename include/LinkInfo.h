#pragma once


#include <iostream>


namespace TrafficEngineering  {

struct LinkInfo {
    std::string localNodeName;
    std::string remoteNodeName;
    std::string localInterfaceName;
    std::string remoteInterfaceName;
};

} // namespace TrafficEngineering
