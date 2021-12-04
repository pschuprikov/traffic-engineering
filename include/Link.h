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
    const std::string &getLocalInterfaceName() const { return _localInterfaceName; }
    const std::string &getRemoteInterfaceName() const { return _remoteInterfaceName; }
private:
    Node *_localNode;
    Node *_remoteNode;
    std::string _localInterfaceName;
    std::string _remoteInterfaceName;
};

} // namespace TrafficEngineering
