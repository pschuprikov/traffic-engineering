#include "Tunnel.h"


namespace TrafficEngineering  {

bool Tunnel::addLink(const Link &link) {
    auto localNodeName = link.getLocalNode()->getName();
    auto remoteNodeName = link.getRemoteNode()->getName();

    if (!containsNode(localNodeName) || containsNode(remoteNodeName)) {
        return false;
    }

    _nodes.insert({remoteNodeName, Node(remoteNodeName)});

    Node &localNode = getNodeByName(localNodeName);
    Node &remoteNode = getNodeByName(remoteNodeName);

    localNode.addInterface(&remoteNode, {localNodeName, remoteNodeName, link.getInterface()});

    return true;
}

bool Tunnel::containsNode(const std::string &name) {
    return name == _root.getName() || _nodes.count(name) != 0;
}

Node &Tunnel::getNodeByName(const std::string &name) {
    if (name == _root.getName()) {
        return _root;
    }
    return _nodes.at(name);
}

} // namespace TrafficEngineering

