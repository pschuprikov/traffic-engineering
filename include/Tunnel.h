#pragma once


#include <unordered_map>
#include <vector>

#include "Node.h"
#include "Link.h"
#include "LinkInfo.h"


namespace TrafficEngineering  {

class Tunnel {
public:
    Tunnel() = delete;
    Tunnel(const Node& root) : _root(root.getName()) {}

    bool addLink(const Link &link);

    int getLoadSize() const { return _loadSize; }
    const std::string &getRootName() const;
    std::vector<const Node *> getDFSOrder() const;
    const std::string &getInInterface(const std::string &nodeName) const;

    std::vector<LinkInfo> getAllLinks() const;

    void setLoadSize(int loadSize);
    void setPeriod(int period);
private:
    bool containsNode(const std::string &name) const;

    Node &getNodeByName(const std::string &name);
    std::vector<const Node *> dfs(const Node &node) const;
private:
    Node _root;
    std::unordered_map<std::string, Node> _nodes;
    std::unordered_map<std::string, std::string> _inInterface;

    int _loadSize;
    int _period;
};

} // namespace TrafficEngineering
