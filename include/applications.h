#pragma once


#include <iostream>
#include <vector>

#include <omnetpp.h>


namespace TrafficEngineering {

struct AppDescription {
    std::string destAddresses;
    int destPort;
    int messageLength;
    double startTime;
    double stopTime;
    double sendInterval;
    bool joinLocalMulticastGroups = true;

    std::string appName;
    std::string appOwnerName;
    std::vector<std::string> appReceiverNames;
};

omnetpp::cModule *createUdpBasicApp(omnetpp::cModule *controller,
                                    const AppDescription &appDescription);

} // namespace TrafficEngineering
