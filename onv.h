#ifndef ONV_H
#define ONV_H

#include <string>

namespace ONVIF {

    struct probe{
        std::string messageId;
        std::string net_handle;
    };

    ONVIF::probe DiscoverySendProbe(std::string scopes, std::string types);
    ONVIF::probe DiscoveryReadResponse(probe probe);
}

#endif // ONV_H
