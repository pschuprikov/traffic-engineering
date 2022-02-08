#pragma once

#include <iostream>
#include <vector>

#include <omnetpp.h>

#include "applications.h"
#include "algorithms.h"
#include "Tunnel.h"


namespace TrafficEngineering {

struct EventDescription {
    std::string node;
    std::string packetName;
    omnetpp::simtime_t time;
};

class SimulationState {
public:
    static SimulationState &getInstance(omnetpp::cModule *controller);

    SimulationState(SimulationState const &) = delete;
    void operator=(SimulationState const &) = delete;

    void logTunnelDescription(const AppDescription &app) const;
    void logEvent(const EventDescription &event) const;
    void logAdjustmentResult(const std::vector<AdjustmentResult> &result) const;

    AppDescription getNextApp();
    const std::vector<Tunnel> &getTunnels() const;

    void addTunnel(const Tunnel &tunnel);
private:
    SimulationState(omnetpp::cModule *controller);

    std::string getNextMulticastGroup();
    std::string getNextAppName();
    const std::string &getNextAppOwnerName();
    std::vector<std::string> getNextAppReceiverNames(const std::string &appOwnerName);
private:
    std::vector<int> _bytes = {225, 0, 0, 1};
    std::string _appNamePrefix = "app-";
    int _counter = 0;

    const std::string _eventsLogFilename = "results/events.log";
    const std::string _tunnelDescriptionFilename = "results/tunnel_descriptions.log";
    const std::string _adjustmentResultFilename = "results/adjustment.log";

    std::vector<std::string> _appOwnerNames;
    std::vector<Tunnel> _tunnels;
private:
    const omnetpp::cPar &_messageLength;
    const omnetpp::cPar &_sendInterval;
    const omnetpp::cPar &_duration;
};

} // namespace TrafficEngineering
