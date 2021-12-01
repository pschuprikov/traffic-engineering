#pragma once


#include <map>
#include <vector>

#include "Node.h"
#include "Link.h"


namespace TrafficEngineering  {

class Tunnel {
public:
    Tunnel() = delete;
    Tunnel(const Node& root) : _root(root.getName()) {}

    bool addLink(const Link &link);

    const std::string &getRootName() const;
    std::vector<const Node *> getDFSOrder() const;
private:
    bool containsNode(const std::string &name) const;

    Node &getNodeByName(const std::string &name);

    void dfs(const Node &node, std::vector<const Node *> &result) const;
private:
    Node _root;
    std::map<std::string, Node> _nodes;
};

} // namespace TrafficEngineering
