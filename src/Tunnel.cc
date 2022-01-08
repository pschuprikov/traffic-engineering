#include "Tunnel.h"


namespace TrafficEngineering  {

bool Tunnel::addLink(const Link &link) {
    auto localNodeName = link.getLocalNode()->getName();
    auto remoteNodeName = link.getRemoteNode()->getName();

    if (!containsNode(localNodeName) || containsNode(remoteNodeName)) {
        return false;
    }

    _nodes.insert({remoteNodeName, Node(remoteNodeName)});
    _inInterface.insert({remoteNodeName, link.getRemoteInterfaceName()});

    Node &localNode = getNodeByName(localNodeName);
    Node &remoteNode = getNodeByName(remoteNodeName);

    localNode.addInterface(&remoteNode, {localNodeName, remoteNodeName, link.getLocalInterfaceName(), link.getRemoteInterfaceName()});

    return true;
}

const std::string &Tunnel::getRootName() const {
    return _root.getName();
}

std::vector<const Node *> Tunnel::getDFSOrder() const {
    return dfs(_root);
}

const std::string &Tunnel::getInInterface(const std::string &nodeName) const {
    return _inInterface.at(nodeName);
}

std::vector<LinkInfo> Tunnel::getAllLinks() const {
    std::vector<LinkInfo> result = _root.getAllLinks();
    for (const auto &entry : _nodes) {
        auto links = entry.second.getAllLinks();
        result.insert(result.end(), links.begin(), links.end());
    }
    return result;
}

void Tunnel::setLoadSize(int loadSize) {
    _loadSize = loadSize;
}

void Tunnel::setPeriod(int period) {
    _period = period;
}

std::vector<const Node *> Tunnel::dfs(const Node &node) const {
    std::vector<const Node *> result = {&node};
    for (const auto &interface : node.getInterfaces()) {
        const Link &link = node.getLinkByInterfaceName(interface);
        Node *nextNode = link.getRemoteNode();
        auto others = dfs(*nextNode);
        result.insert(result.end(), others.begin(), others.end());
    }
    return result;
}

bool Tunnel::containsNode(const std::string &name) const {
    return name == _root.getName() || _nodes.count(name) != 0;
}

Node &Tunnel::getNodeByName(const std::string &name) {
    if (name == _root.getName()) {
        return _root;
    }
    return _nodes.at(name);
}

} // namespace TrafficEngineering

