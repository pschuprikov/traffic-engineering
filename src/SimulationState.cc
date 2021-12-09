#include "SimulationState.h"


namespace TrafficEngineering {

SimulationState &SimulationState::getInstance(const std::vector<std::string> &appOwnerNames) {
    static SimulationState instance(appOwnerNames);
    return instance;
}

AppDescription SimulationState::getNextApp() {
    AppDescription appDescription;
    appDescription.destPort = 100;
    appDescription.messageLength = 500;
    appDescription.sendInterval = 0.1;
    appDescription.startTime = 0.15;
    appDescription.stopTime = 0.2;
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
