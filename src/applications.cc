#include "applications.h"


namespace TrafficEngineering {

omnetpp::cModule *createUdpBasicApp(omnetpp::cModule *controller,
                       const AppDescription &appDescription) {

    auto *messageSource = controller->getModuleByPath(appDescription.request.appOwnerName.c_str());
    auto *dispatcher = messageSource->getSubmodule("at");

    auto *applicationFactory = omnetpp::cModuleType::get("inet.applications.udpapp.UdpBasicApp");
    auto *app = applicationFactory->create(appDescription.appName.c_str(), messageSource);
    auto *socketIn = app->gate("socketIn");
    auto *socketOut = app->gate("socketOut");

    auto *inGate = dispatcher->getOrCreateFirstUnconnectedGate("in", 0, false, true);
    auto *outGate = dispatcher->getOrCreateFirstUnconnectedGate("out", 0, false, true);

    socketOut->connectTo(inGate);
    outGate->connectTo(socketIn);

    app->par("destPort") = appDescription.destPort;
    app->par("messageLength") = appDescription.request.messageLength;
    app->par("startTime") = appDescription.startTime;
    app->par("sendInterval") = appDescription.request.sendInterval;
    app->par("destAddresses") = appDescription.destAddresses;
    app->par("joinLocalMulticastGroups") = appDescription.joinLocalMulticastGroups;
    app->par("packetName") = appDescription.appName;
    app->finalizeParameters();

    app->buildInside();
    app->scheduleStart(controller->getSimulation()->getSimTime());
    app->callInitialize();

    return app;
}

} // namespace TrafficEngineering
