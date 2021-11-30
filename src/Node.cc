#include "Node.h"

#include <vector>


namespace TrafficEngineering  {

void Node::addInterface(Node *remoteNode, const LinkInfo &linkInfo) {
    _interfaces.insert({linkInfo.interfaceName, Link(this, remoteNode, linkInfo)});
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

} // namespace TrafficEngineering
