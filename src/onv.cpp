#include "onv.h"
#include "app.h"

ONVIF::probe ONVIF::DiscoverySendProbe(std::string scopes, std::string types) {

    App *app = new App();
    ONVIF::probe probe;

    //app->probe.messageId = "uuid:" + app->uuidGenerate();
    //std::cout << "UUID: " << pro.messageId << std::endl;
    std::string message = app->buildProbeMessage("uuid:" + app->uuidGenerate(), scopes, types);

    // Send probe to multicast address and port according to [WS-Discovery] section 2.4
    //probe.net_handle = app->send_multicast("239.255.255.250", 3702, message);
    probe.net_handle = app->sendMulticast("239.255.255.250", 3702, message);

    delete app;

    return probe;
}


ONVIF::probematch ONVIF::DiscoveryReadResponse(ONVIF::probe probe)
{
    App *app = new App();
    ONVIF::probematch aProbeMatches;
    ONVIF::probematch match;
    std::string header; //der sollte eigentlich aus der Antwort kommen..
        /*header ist xml-struct mit
         *PROBE:
         *<e:Header>
            <w:MessageID>uuid:84ede3de-7dec-11d0-c360-f01234567890</w:MessageID>
            <w:To e:mustUnderstand="true">urn:schemas-xmlsoap-org:ws:2005:04:discovery</w:To>
            [...]
          </e:Header>

        RESPONSE:
        <SOAP-ENV:Header>
            <wsa:MessageID>uuid:84ede3de-e374-11df-b259-00408c1836b2</wsa:MessageID>
            <wsa:RelatesTo>uuid:84ede3de-7dec-11d0-c360-F01234567890</wsa:RelatesTo>
            <wsa:To SOAP-ENV:mustUnderstand="true">http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</wsa:To>
            [...]
        </SOAP-ENV:Header>*/

    // Read response and process it.
    // We need both the body and the Header:
    aProbeMatches = app->readProbeMatches(probe.net_handle, header);

    // Check if this is a response to the probe we sent:
    //if (Header.RelatesTo != probe.MessageID) {
    if(!header.compare(probe.messageId)){
        delete app;
        ONVIF::probematch p;
        p.endpointAddress = "";
        return p;
    }

    // We pick what we need from the response:
    match.types = aProbeMatches.types;
    match.scopes = aProbeMatches.scopes;

    // XAddrs is a space separated list of URLs to the Device service:
    match.xAddrs          = aProbeMatches.xAddrs;
    match.metadataVersion = aProbeMatches.metadataVersion;
    match.endpointAddress = aProbeMatches.endpointAddress;

    delete app;
    return match;
}

void ONVIF::ProcessMatch(ONVIF::probematch match){
    //do sth.
}
