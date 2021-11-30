#pragma once


#include <map>

#include "Node.h"
#include "Link.h"


namespace TrafficEngineering  {

class Tunnel {
public:
    Tunnel() = delete;
    Tunnel(const Node& root) : _root(root.getName()) {}

    bool addLink(const Link &link);
private:
    bool containsNode(const std::string &name);

    Node &getNodeByName(const std::string &name);
private:
    Node _root;
    std::map<std::string, Node> _nodes;
};

} // namespace TrafficEngineering
