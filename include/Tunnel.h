#pragma once

#include <omnetpp.h>

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

    double getLoadSize() const { return 8 * (_loadSize + 54); }
    const std::string &getRootName() const;
    std::vector<Node> getDFSOrder() const;
    const std::string &getInInterface(const std::string &nodeName) const;
    const Node &getNode(const std::string &name) const;
    const Node &getRoot() const { return _root; }
    double getPeriod() const;

    std::vector<Link> getAllLinks() const;

    void setLoadSize(double loadSize);
    void setPeriod(omnetpp::cPar *period);
    void setPeriodValue(double period);
private:
    bool containsNode(const std::string &name) const;

    Node &getNodeByName(const std::string &name);
    std::vector<Node> dfs(const Node &node) const;
private:
    Node _root;
    std::unordered_map<std::string, Node> _nodes;
    std::unordered_map<std::string, std::string> _inInterface;

    double _loadSize;
    omnetpp::cPar *_period;
};

} // namespace TrafficEngineering
