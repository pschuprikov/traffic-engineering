#include "Node.h"

#include <vector>


namespace TrafficEngineering  {

void Node::addInterface(Node *remoteNode, const LinkInfo &linkInfo) {
    _interfaces.insert({linkInfo.localInterfaceName, Link(this, remoteNode, linkInfo)});
    _next.insert({linkInfo.remoteNodeName, Link(this, remoteNode, linkInfo)});
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

std::vector<LinkInfo> Node::getAllLinks() const {
    std::vector<LinkInfo> result;
    for (const auto &entry : _interfaces) {
        result.emplace_back(entry.second.toLinkInfo());
    }
    return result;
}

} // namespace TrafficEngineering
