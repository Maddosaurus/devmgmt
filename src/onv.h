#ifndef ONV_H
#define ONV_H

#include <string>

namespace ONVIF {

    struct probe{
        std::string messageId;
        std::string net_handle;
    };

    struct probematch{
        std::string types;
        std::string scopes;
        std::string xAddrs;
        std::string metadataVersion;
        std::string endpointAddress;
    };

    ONVIF::probe DiscoverySendProbe(std::string scopes, std::string types);
    ONVIF::probematch DiscoveryReadResponse(probe probe);
    void ProcessMatch(probematch match);
}

#endif // ONV_H
