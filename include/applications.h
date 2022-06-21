#pragma once


#include <iostream>
#include <vector>

#include <omnetpp.h>


namespace TrafficEngineering {

struct MulticastRequest {
    int messageLength;
    double sendInterval;
    std::string appOwnerName;
    std::vector<std::string> appReceiverNames;
};

struct AppDescription {
    MulticastRequest request;
    std::string destAddresses;
    int destPort;
    double startTime;
    double stopTime;
    bool joinLocalMulticastGroups = true;

    std::string appName;
};

void createUdpBasicApp(omnetpp::cModule *controller,
                       const AppDescription &appDescription);

} // namespace TrafficEngineering
