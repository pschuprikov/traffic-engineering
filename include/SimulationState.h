#pragma once

#include <iostream>
#include <vector>

#include <omnetpp.h>

#include "applications.h"


namespace TrafficEngineering {

class SimulationState {
public:
    static SimulationState &getInstance(omnetpp::cModule *controller);

    SimulationState(SimulationState const &) = delete;
    void operator=(SimulationState const &) = delete;

    AppDescription getNextApp();

private:
    std::string getNextMulticastGroup();
    std::string getNextAppName();
    const std::string &getNextAppOwnerName();

    SimulationState(omnetpp::cModule *controller);
private:
    std::vector<int> _bytes = {225, 0, 0, 1};
    std::string _appNamePrefix = "app#";
    int _counter = 0;

    std::vector<std::string> _appOwnerNames;
private:
    const omnetpp::cPar &_messageLength;
    const omnetpp::cPar &_sendInterval;
    const omnetpp::cPar &_duration;
};

} // namespace TrafficEngineering
