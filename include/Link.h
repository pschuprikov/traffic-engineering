#pragma once


#include "LinkInfo.h"


namespace TrafficEngineering  {

class Node;

class Link {
public:
    Link() = delete;
    Link(Node *localNode, Node *remoteNode, const LinkInfo &linkInfo);

    Node *getLocalNode() const { return _localNode; }
    Node *getRemoteNode() const { return _remoteNode; }
    const std::string &getInterface() const { return _interfaceName; }
private:
    Node *_localNode;
    Node *_remoteNode;
    std::string _interfaceName;
};

} // namespace TrafficEngineering
