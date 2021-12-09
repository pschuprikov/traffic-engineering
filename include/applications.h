#pragma once


#include <iostream>

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
};

void createUdpBasicApp(omnetpp::cModule *controller,
                       const AppDescription &appDescription);

} // namespace TrafficEngineering
