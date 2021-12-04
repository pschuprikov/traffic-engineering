#include <omnetpp.h>

#include "inet/networklayer/contract/ipv4/Ipv4Address.h"

#include "multicast.h"
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

    Tunnel tunnel = getSpanningTree(topology, "server5");

    addMulticastTunnel(this, tunnel, inet::Ipv4Address("225.0.0.2"));

    std::vector<const Node *> nodes = tunnel.getDFSOrder();
    for (const Node *node : nodes) {
        std::cout << node->getName() << ' ';
        std::cout << '(';
        for (const auto &interface : node->getInterfaces()) {
            std::cout << interface << ' ';
        }
        std::cout << ')';
    }
    std::cout << '\n';

    send(msg, "out");
}
