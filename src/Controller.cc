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

    for (int i = 0; i < 1; i++) {
        auto appDescription = state.getNextApp();
        appDescription.appReceiverNames.push_back("server2");
        createUdpBasicApp(this, appDescription);

        state.logTunnelDescription(appDescription);

        Topology topology = makeTopologyFromCurrentNetwork();
        Tunnel tunnel = optimization(topology, state.getTunnels(), appDescription);
        addMulticastGroup(this, tunnel, appDescription.destAddresses);

        state.addTunnel(tunnel);

        // appDescription.appName = "app-1";
        // appDescription.destAddresses = "225.0.0.2";
        // createUdpBasicApp(this, appDescription);
        // addMulticastGroup(this, tunnel, appDescription.destAddresses);
    }

    auto result = adjustment(state.getTunnels());
    state.logAdjustmentResult(result);

    // send(msg, "out");
}
