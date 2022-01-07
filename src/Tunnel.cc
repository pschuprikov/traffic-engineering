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
    std::vector<const Node *> result;
    dfs(_root, result);
    return result;
}

const std::string &Tunnel::getInInterface(const std::string &nodeName) const {
    return _inInterface.at(nodeName);
}

std::vector<LinkInfo> Tunnel::getAllLinks() const {
    std::vector<LinkInfo> result;
    for (const auto *node : getDFSOrder()) {
        auto links = node->getAllLinks();
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

void Tunnel::dfs(const Node &node, std::vector<const Node *> &result) const {
    result.push_back(&node);
    for (const auto &interface : node.getInterfaces()) {
        const Link &link = node.getLinkByInterfaceName(interface);
        Node *nextNode = link.getRemoteNode();
        dfs(*nextNode, result);
    }
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

