#include <omnetpp.h>

#include "inet/networklayer/contract/ipv4/Ipv4Address.h"

#include "algorithms.h"

#include "applications.h"
#include "multicast.h"
#include "tools.h"
#include "SimulationState.h"

#include <fstream>


using namespace TrafficEngineering;
using namespace omnetpp;


class Controller : public cSimpleModule {
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
};


Define_Module(Controller);


void Controller::initialize() {
    if (strcmp("tic", getName()) != 0) {
        return;
    }
    cMessage *msg = new cMessage("vital message");
    send(msg, "out");
}

void Controller::handleMessage(cMessage *msg) {
    auto &state = SimulationState::getInstance(this);

    for (int i = 0; i < 100; i++) {
        auto appDescription = state.getNextApp();
        auto *app = createUdpBasicApp(this, appDescription);

        state.logTunnelDescription(appDescription);

        Topology topology = makeTopologyFromCurrentNetwork();
        Tunnel tunnel = optimization(topology, state.getTunnels(), appDescription);
        tunnel.setPeriod(&app->par("sendInterval"));
        addMulticastGroup(this, tunnel, appDescription.destAddresses);

        state.addTunnel(tunnel);
    }

    auto result = adjustment(state.getTunnels());
    state.logAdjustmentResult(result);

    send(msg, "out");
}
