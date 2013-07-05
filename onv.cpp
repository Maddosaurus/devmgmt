#include "onv.h"

ONVIF::probe ONVIF::DiscoverySendProbe(std::string scopes, std::string types) {

    App *app = new App();

    //app->probe.messageId = "uuid:" + app->uuidGenerate();
    //std::cout << "UUID: " << pro.messageId << std::endl;
    message = app->buildProbeMessage("uuid:" + app->uuidGenerate(), scopes, types);

    // Send probe to multicast address and port according to [WS-Discovery] section 2.4
    probe.net_handle = App.send_multicast("239.255.255.250", 3702, message);

    delete app;

    return probe;
}


ONVIF::probematch ONVIF::DiscoveryReadResponse(ONVIF::probe probe)
{
    App *app = new App();
    ONVIF::probematch aProbeMatches;
    ONVIF::probematch match;

    // Read response and process it.
    // We need both the body and the Header:
    aProbeMatches = app->ReadProbeMatches(probe.net_handle, Header);

    // Check if this is a response to the probe we sent:
    if (Header.RelatesTo != probe.MessageID) {

        delete app;
        return -1;
    }

    // We pick what we need from the response:
    match.types = aProbeMatches.Types;
    match.scopes = aProbeMatches.Scopes;

    // XAddrs is a space separated list of URLs to the Device service:
    match.xaddrs = aProbeMatches.XAddrs;
    match.metadataversion = aProbeMatches.MetadataVersion;
    match.address = aProbeMatches.EndpointAddress;

    delete app;
    return match;
}
