#pragma once


#include <iostream>
#include <map>
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
private:
    void createNode(const std::string &name);
private:
    std::map<std::string, Node> _nodes;
};

} // namespace TrafficEngineering
