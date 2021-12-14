#include <omnetpp.h>

#include "inet/networklayer/contract/ipv4/Ipv4Address.h"

#include "applications.h"
#include "multicast.h"
#include "tools.h"
#include "SimulationState.h"


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
    auto &state = SimulationState::getInstance({"server1", "server3", "server5", "server7"});

    auto appDescription = state.getNextApp();
    addMulticastGroup(this, appDescription.appOwnerName, appDescription.destAddresses);
    createUdpBasicApp(this, appDescription);

    send(msg, "out");
}
