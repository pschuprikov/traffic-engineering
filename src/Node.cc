#include "Node.h"

#include <vector>


namespace TrafficEngineering  {

void Node::addInterface(Node *remoteNode, const Link &link) {
    _interfaces.insert({link.localInterfaceName, link});
    _next.insert({link.remoteNodeName, link});
}

std::vector<std::string> Node::getInterfaces() const {
    std::vector<std::string> result;
    for (const auto &entry : _interfaces) {
        result.emplace_back(entry.first);
    }
    return result;
}

int Node::getInterfaceNumber() const {
    return _interfaces.size();
}

const Link &Node::getLinkByInterfaceName(const std::string &interfaceName) const {
    return _interfaces.at(interfaceName);
}

const Link &Node::getLinkByNodeName(const std::string &nodeName) const {
    return _next.at(nodeName);
}

std::vector<Link> Node::getAllLinks() const {
    std::vector<Link> result;
    for (const auto &entry : _interfaces) {
        result.push_back(entry.second);
    }
    return result;
}

} // namespace TrafficEngineering
