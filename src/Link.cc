#include "Link.h"

#include "Node.h"


namespace TrafficEngineering  {

Link::Link(Node *localNode, Node *remoteNode, const LinkInfo &linkInfo) :
        _localNode(localNode),
        _remoteNode(remoteNode),
        _localInterfaceName(linkInfo.localInterfaceName),
        _remoteInterfaceName(linkInfo.remoteInterfaceName),
        _datarate(linkInfo.datarate)
{

}

LinkInfo Link::toLinkInfo() const {
    LinkInfo result;
    result.localNodeName = _localNode->getName();
    result.remoteNodeName = _remoteNode->getName();
    result.localInterfaceName = _localInterfaceName;
    result.remoteInterfaceName = _remoteInterfaceName;
    result.datarate = _datarate;
    return result;
}

} // namespace TrafficEngineering
