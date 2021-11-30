#include "Link.h"


namespace TrafficEngineering  {

Link::Link(Node *localNode, Node *remoteNode, const LinkInfo &linkInfo) :
        _localNode(localNode),
        _remoteNode(remoteNode),
        _interfaceName(linkInfo.interfaceName)
{

}

} // namespace TrafficEngineering
