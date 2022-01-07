#pragma once


#include <iostream>
#include <unordered_map>
#include <vector>

#include "LinkInfo.h"
#include "Node.h"


namespace TrafficEngineering  {

class Topology {
public:
    Topology() = default;

    void addLink(const LinkInfo &linkInfo);

    int getNodeNumber() const { return _nodes.size(); }
    const Node &getNodeByName(const std::string &name) const;
    std::vector<std::string> getAllNodeNames() const;

    const Link &getLink(const std::string &from, const std::string &to) const;
    std::vector<LinkInfo> getAllLinks() const;
private:
    void createNode(const std::string &name);
private:
    std::unordered_map<std::string, Node> _nodes;
};

} // namespace TrafficEngineering
