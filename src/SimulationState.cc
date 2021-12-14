#include "SimulationState.h"

#include "tools.h"


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
}

AppDescription SimulationState::getNextApp() {
    AppDescription appDescription;
    appDescription.destPort = 100;
    appDescription.messageLength = static_cast<int>(_messageLength.doubleValue());
    appDescription.sendInterval = _sendInterval.doubleValue();
    appDescription.startTime = 0.15;
    appDescription.stopTime = appDescription.startTime + _duration.doubleValue();
    appDescription.destAddresses = getNextMulticastGroup();
    appDescription.appName = getNextAppName();
    appDescription.appOwnerName = getNextAppOwnerName();
    return appDescription;
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
    return _appNamePrefix + std::to_string(++_counter);
}

const std::string &SimulationState::getNextAppOwnerName() {
    int index = rand() % _appOwnerNames.size();
    return _appOwnerNames.at(index);
}

} // namespace TrafficEngineering
