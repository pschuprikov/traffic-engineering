#pragma once


#include <map>

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
    const Link &getLink(const std::string &interfaceName) const;

    std::vector<LinkInfo> getAllLinks() const;
private:
    std::string _name;
    std::map<std::string, Link> _interfaces;
};

} // namespace TrafficEngineering
