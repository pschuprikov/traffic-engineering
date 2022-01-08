#pragma once


#include <Link.h>
#include <unordered_map>
#include <vector>

#include "Node.h"
#include "Link.h"


namespace TrafficEngineering  {

class Tunnel {
public:
    Tunnel() = delete;
    Tunnel(const Node &root) : _root(root.getName()) {}

    bool addLink(const Link &link);

    int getLoadSize() const { return _loadSize; }
    const std::string &getRootName() const;
    std::vector<Node> getDFSOrder() const;
    const std::string &getInInterface(const std::string &nodeName) const;

    std::vector<Link> getAllLinks() const;

    void setLoadSize(int loadSize);
    void setPeriod(int period);
private:
    bool containsNode(const std::string &name) const;

    Node &getNodeByName(const std::string &name);
    std::vector<Node> dfs(const Node &node) const;
private:
    Node _root;
    std::unordered_map<std::string, Node> _nodes;
    std::unordered_map<std::string, std::string> _inInterface;

    int _loadSize;
    int _period;
};

} // namespace TrafficEngineering
