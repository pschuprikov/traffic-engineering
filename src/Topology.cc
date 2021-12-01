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

std::vector<std::string> Topology::getAllNodeNames() const {
    std::vector<std::string> result;
    for (const auto &entry : _nodes) {
        result.emplace_back(entry.first);
    }
    return result;
}

void Topology::createNode(const std::string &name) {
    _nodes.insert({name, Node(name)});
}

} // namespace TrafficEngineering