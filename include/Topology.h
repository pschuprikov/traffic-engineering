#pragma once


#include <Link.h>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "Node.h"


namespace TrafficEngineering  {

class Topology {
public:
    Topology() = default;

    void addLink(const Link &link);

    int getNodeNumber() const { return _nodes.size(); }
    const Node &getNodeByName(const std::string &name) const;
    std::vector<std::string> getAllNodeNames() const;

    const Link &getLink(const std::string &from, const std::string &to) const;
    std::vector<Link> getAllLinks() const;
private:
    void createNode(const std::string &name);
private:
    std::unordered_map<std::string, Node> _nodes;
};

} // namespace TrafficEngineering
