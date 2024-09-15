#pragma once


#include <iostream>
#include <vector>

#include <omnetpp.h>


namespace TrafficEngineering {

enum class EntityKind {

};

template <EntityKind K>
struct Name { const std::string name; };


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

void createUdpBasicApp(omnetpp::cModule *controller,
                       const AppDescription &appDescription);

} // namespace TrafficEngineering
