#ifndef ONV_H
#define ONV_H

#include <string>

namespace ONVIF {

    struct probe{
        std::string messageId;
        std::string net_handle;
    };

    struct probematch{
        std::string Types;
        std::string Scopes;
        std::string XAddrs;
        std::string MetadataVersion;
        std::string EndpointAddress;
    };

    ONVIF::probe DiscoverySendProbe(std::string scopes, std::string types);
    ONVIF::probematch DiscoveryReadResponse(probe probe);
}

#endif // ONV_H
