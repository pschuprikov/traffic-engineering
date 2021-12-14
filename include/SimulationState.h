#pragma once

#include <iostream>
#include <vector>

#include "applications.h"


namespace TrafficEngineering {

class SimulationState {
public:
    static SimulationState &getInstance();

    SimulationState(SimulationState const &) = delete;
    void operator=(SimulationState const &) = delete;

    AppDescription getNextApp();

private:
    std::string getNextMulticastGroup();
    std::string getNextAppName();
    const std::string &getNextAppOwnerName();

    SimulationState();
private:
    std::vector<int> _bytes = {225, 0, 0, 1};
    std::string _appNamePrefix = "app#";
    int _counter = 0;

    std::vector<std::string> _appOwnerNames;
};

} // namespace TrafficEngineering
