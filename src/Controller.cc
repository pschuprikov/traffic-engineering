#include <omnetpp.h>

#include "tools.h"


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
    Topology topology = makeTopologyFromCurrentNetwork();
    std::cout << "Number of nodes is " << topology.getNodeNumber() << '\n';
    send(msg, "out");
}
