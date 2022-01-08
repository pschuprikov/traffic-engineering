#include "Tunnel.h"


namespace TrafficEngineering  {

bool Tunnel::addLink(const Link &link) {
    if (!containsNode(link.localNodeName) || containsNode(link.remoteNodeName)) {
        return false;
    }

    _nodes.insert({link.remoteNodeName, Node(link.remoteNodeName)});
    _inInterface.insert({link.remoteNodeName, link.remoteInterfaceName});

    Node &localNode = getNodeByName(link.localNodeName);

    localNode.addInterface(link);

    return true;
}

const std::string &Tunnel::getRootName() const {
    return _root.getName();
}

std::vector<Node> Tunnel::getDFSOrder() const {
    return dfs(_root);
}

const std::string &Tunnel::getInInterface(const std::string &nodeName) const {
    return _inInterface.at(nodeName);
}

const Node &Tunnel::getNode(const std::string &name) const {
    if (name == _root.getName()) {
        return _root;
    }
    return _nodes.at(name);
}

std::vector<Link> Tunnel::getAllLinks() const {
    std::vector<Link> result = _root.getAllLinks();
    for (const auto &entry : _nodes) {
        auto links = entry.second.getAllLinks();
        result.insert(result.end(), links.begin(), links.end());
    }
    return result;
}

void Tunnel::setLoadSize(double loadSize) {
    _loadSize = loadSize;
}

void Tunnel::setPeriod(double period) {
    _period = period;
}

std::vector<Node> Tunnel::dfs(const Node &node) const {
    std::vector<Node> result = {node};
    for (const auto &interface : node.getInterfaces()) {
        const Link &link = node.getLinkByInterfaceName(interface);
        auto others = dfs(_nodes.at(link.remoteNodeName));
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

