#include "onv.h"

Service::probe ONVIF::DiscoverySendProbe(std::string scopes, std::string types) {

    App *app = new App();

    //app->probe.messageId = "uuid:" + app->uuidGenerate();
    //std::cout << "UUID: " << pro.messageId << std::endl;
    message = app->buildProbeMessage("uuid:" + app->uuidGenerate(), "dn:NetworkVideoTransmitter", "");

    // Send probe to multicast address and port according to [WS-Discovery] section 2.4
    probe.net_handle = App.send_multicast("239.255.255.250", 3702, message);

    delete app;

    return probe;
}


Service::probe ONVIF::DiscoveryReadResponse(Service::probe probe)
{
    // Read response and process it.
    // We need both the body and the Header:
    aProbeMatches = App.ReadProbeMatches(probe.net_handle, Header);

    // Check if this is a response to the probe we sent:
    if (Header.RelatesTo != probe.MessageID) {
        return -1;
    }

    // We pick what we need from the response:
    probematch.types = aProbeMatches.ProbeMatch.Types;
    probematch.scopes = aProbeMatches.ProbeMatch.Scopes;

    // XAddrs is a space separated list of URLs to the Device service:
    probematch.xaddrs = aProbeMatches.ProbeMatch.XAddrs;
    probematch.metadataversion = aProbeMatches.ProbeMatch.MetadataVersion;
    probematch.address = aProbeMatches.ProbeMatch.EndpointReference.Address;

    return probematch;
}
