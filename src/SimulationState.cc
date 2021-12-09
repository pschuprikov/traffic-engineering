#include "SimulationState.h"


namespace TrafficEngineering {

SimulationState &SimulationState::getInstance() {
    static SimulationState instance;
    return instance;
}

} // namespace TrafficEngineering
