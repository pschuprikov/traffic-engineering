#include "Node.h"

#include <vector>


namespace TrafficEngineering  {

void Node::addInterface(Node *remoteNode, const LinkInfo &linkInfo) {
    _interfaces.insert({linkInfo.localInterfaceName, Link(this, remoteNode, linkInfo)});
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

const Link &Node::getLink(const std::string &interfaceName) const {
    return _interfaces.at(interfaceName);
}

std::vector<std::string> Node::getAllNeighbours() const {
    std::vector<std::string> result;
    for (const auto &entry : _interfaces) {
        auto *node = entry.second.getRemoteNode();
        result.emplace_back(node->getName());
    }
    return result;
}

} // namespace TrafficEngineering
