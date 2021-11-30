#include "Topology.h"


namespace TrafficEngineering  {

void Topology::addLink(const LinkInfo &linkInfo) {
    createNode(linkInfo.localNodeName);
    createNode(linkInfo.remoteNodeName);
    Node &localNode = _nodes.at(linkInfo.localNodeName);
    Node &remoteNode = _nodes.at(linkInfo.remoteNodeName);
    localNode.addInterface(&remoteNode, linkInfo);
}

const Node &Topology::getNodeByName(const std::string &name) const {
    return _nodes.at(name);
}

void Topology::createNode(const std::string &name) {
    _nodes.insert({name, Node(name)});
}

} // namespace TrafficEngineering
