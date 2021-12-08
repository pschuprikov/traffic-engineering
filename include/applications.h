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
};

void createUdpBasicApp(omnetpp::cModule *controller,
                       const std::string &appName,
                       const std::string &appOwnerName,
                       const AppDescription &appDescription);

} // namespace TrafficEngineering
