#pragma once


#include <unordered_map>

#include "Link.h"


namespace TrafficEngineering  {

class Node {
public:
    Node() = delete;
    explicit Node(std::string name) : _name(std::move(name)) {}

    void addInterface(Node *remoteNode, const LinkInfo &linkInfo);

    const std::string &getName() const { return _name; }
    std::vector<std::string> getInterfaces() const;
    int getInterfaceNumber() const;
    const Link &getLinkByInterfaceName(const std::string &interfaceName) const;
    const Link &getLinkByNodeName(const std::string &nodeName) const;

    std::vector<LinkInfo> getAllLinks() const;
private:
    std::string _name;
    std::unordered_map<std::string, Link> _interfaces;
    std::unordered_map<std::string, Link> _next;
};

} // namespace TrafficEngineering
