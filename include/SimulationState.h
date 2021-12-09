#pragma once


namespace TrafficEngineering {

class SimulationState {
    public:
        static SimulationState &getInstance();
    private:
        SimulationState() = default;
        SimulationState(SimulationState const &) = delete;
        void operator=(SimulationState const &) = delete;
 };

} // namespace TrafficEngineering
