#include "SimulationState.h"

#include "tools.h"

#include <fstream>
#include <cstdio>


namespace TrafficEngineering {

SimulationState &SimulationState::getInstance(omnetpp::cModule *controller) {
    static SimulationState instance(controller);
    return instance;
}

SimulationState::SimulationState(omnetpp::cModule *controller) :
    _messageLength(controller->par("messageLength")),
    _sendInterval(controller->par("sendInterval")),
    _duration(controller->par("duration"))
{
    _appOwnerNames = getSourceFromCurrentNetwork();

    std::remove(_eventsLogFilename.c_str());
    std::remove(_tunnelDescriptionFilename.c_str());
}

void SimulationState::logTunnelDescription(const AppDescription &app) const {
    std::ofstream out(_tunnelDescriptionFilename, std::ios::app);
    out << app.request.appOwnerName << ' ';
    for (const auto &receiver : app.request.appReceiverNames) {
        out << receiver << ' ';
    }
    out << '\n';
    out.close();
}

void SimulationState::logEvent(const EventDescription &event) const {
    std::ofstream out(_tunnelDescriptionFilename, std::ios::app);
    out << event.node << ' ';
    out << event.packetName << ' ';
    out << event.time << '\n';
    out.close();
}

void SimulationState::logAdjustmentResult(const std::vector<AdjustmentResult> &result) const {
    std::ofstream out(_adjustmentResultFilename);
    for (const auto &element : result) {
        out << element.minDelay << ' ';
        out << element.maxDelay << ' ';
        out << '\n';
    }
    out.close();
}

AppDescription SimulationState::getNextApp() {
    AppDescription appDescription;
    appDescription.destPort = 100;
    appDescription.request.messageLength = static_cast<int>(_messageLength.doubleValue());
    appDescription.request.sendInterval = _sendInterval.doubleValue();
    appDescription.startTime = 0.15;
    appDescription.stopTime = appDescription.startTime + _duration.doubleValue();
    appDescription.destAddresses = getNextMulticastGroup();
    appDescription.appName = getNextAppName();
    appDescription.request.appOwnerName = getNextAppOwnerName();
    appDescription.request.appReceiverNames = getNextAppReceiverNames(appDescription.request.appOwnerName);
    return appDescription;
}

std::vector<Tunnel> &SimulationState::getTunnels() {
    return _tunnels;
}

void SimulationState::addTunnel(const Tunnel &tunnel) {
    _tunnels.push_back(tunnel);
}

std::string SimulationState::getNextMulticastGroup() {
    std::string result;
    for (int byte : _bytes) {
        result += std::to_string(byte) + '.';
    }
    result.pop_back();

    for (int i = _bytes.size() - 1; i >= 0; i--) {
        _bytes[i] += 1;
        if (_bytes[i] == (1 << 8)) {
            _bytes[i] = 0;
            continue;
        }
        break;
    }

    return result;
}

std::string SimulationState::getNextAppName() {
    return _appNamePrefix + std::to_string(_counter++);
}

const std::string &SimulationState::getNextAppOwnerName() {
    int index = rand() % _appOwnerNames.size();
    return _appOwnerNames.at(index);
}

std::vector<std::string> SimulationState::getNextAppReceiverNames(const std::string &appOwnerName) {
    std::vector<std::string> result;
    std::vector<bool> used(_appOwnerNames.size());
    int receiversNumber = 2 + (rand() % (_appOwnerNames.size() - 2));
    for (int i = 0; i < receiversNumber; i++) {
        int nodeId = rand() % _appOwnerNames.size();
        while (used[nodeId] || _appOwnerNames[nodeId] == appOwnerName) {
            nodeId = rand() % _appOwnerNames.size();
        }
        result.push_back(_appOwnerNames.at(nodeId));
        used[nodeId] = true;
    }
    return result;
}

} // namespace TrafficEngineering
