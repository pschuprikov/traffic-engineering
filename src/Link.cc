#include "Link.h"


namespace TrafficEngineering  {

Link::Link(Node *localNode, Node *remoteNode, const LinkInfo &linkInfo) :
        _localNode(localNode),
        _remoteNode(remoteNode),
        _localInterfaceName(linkInfo.localInterfaceName),
        _remoteInterfaceName(linkInfo.remoteInterfaceName)
{

}

} // namespace TrafficEngineering
