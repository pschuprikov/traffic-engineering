#include <omnetpp.h>

#include "inet/networklayer/contract/ipv4/Ipv4Address.h"

#include "applications.h"
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

    std::string multicastGroup = "225.0.0.2";
    std::string messageSource = "server5";

    Tunnel tunnel = getSpanningTree(topology, messageSource);

    addMulticastTunnel(this, tunnel, inet::Ipv4Address(multicastGroup.c_str()));

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

    AppDescription appDescription;
    appDescription.destPort = 100;
    appDescription.messageLength = 500;
    appDescription.sendInterval = 0.1;
    appDescription.startTime = 0.15;
    appDescription.stopTime = 0.2;
    appDescription.destAddresses = multicastGroup;
    createUdpBasicApp(this, "app", messageSource, appDescription);

    send(msg, "out");
}
