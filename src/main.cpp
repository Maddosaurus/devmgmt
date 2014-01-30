#include <iostream>

#include <boost/array.hpp>
#include <boost/asio.hpp>

#include "src/communication/tcpasyncclient.h"
#include "src/communication/udpsender.h"
#include "src/communication/udpreceiver.h"
#include "helper/xmlhelper.h"
#include "helper/authenticator.h"

void usage(char const* progName) {
    std::cout << "Usage: " << progName << " -r or -s\n";
    std::cout << "\t -r for receiving info \n";
    std::cout << "\t -s for sending a discovery.\n";
    std::cout << "\t Usually, you want to have one receiver and one sender.\n";
}

int main(int argc, char** argv)
{
    bool isReceiver = true;

    //We need at least one switch
    if(argc < 2){
        usage(argv[0]);
        return 1;
    }

    //Get the param
    char* const opt = argv[1];

    //check which param we've got
    if(opt[0] != '-'){
        usage(argv[0]);
        return 1;
    } else if(opt[1] != 'r' && opt[1] != 's'){
        usage(argv[0]);
        return 1;
    }
    if(opt[1] == 's'){
        isReceiver = false;
    }

     XmlHelper *xmlHelper = new XmlHelper;


    //The receiver waits for a WS-Discovery-Multicast and then queries the Stream-URI
    if(isReceiver){
        boost::asio::io_service io_service_udpr;
        boost::asio::io_service io_service_tcp;

        //Generate the digest for authentication purposes
        Authenticator *auth = new Authenticator();
        std::string token[4];
        auth->genToken("admin","pass",token);
        delete auth;

        //Wait for the Multicast
        UdpReceiver r(io_service_udpr, boost::asio::ip::address::from_string("0.0.0.0"), boost::asio::ip::address::from_string("239.255.255.250"));
        io_service_udpr.run();
        io_service_udpr.stop();
        std::cout << "Found a Device: " << r.getFoundDevice() << std::endl;


        QDomDocument docGetURIs = xmlHelper->loadXml("xml/device.GetStreamURI.xml");
        QDomDocument docAuthHeader = xmlHelper->loadXml("xml/auth.xml");


        //---Aufruf von GetStreamURIs
        docGetURIs.elementsByTagName("soap:Envelope").at(0).appendChild((docAuthHeader.elementsByTagName("s:Header").at(0)));

        docGetURIs.elementsByTagName("Username").at(0).firstChild().setNodeValue(token[0].data());
        docGetURIs.elementsByTagName("Password").at(0).firstChild().setNodeValue(token[1].data());
        docGetURIs.elementsByTagName("Nonce").at(0).firstChild().setNodeValue(token[2].data());
        docGetURIs.elementsByTagName("Created").at(0).firstChild().setNodeValue(token[3].data());

        TcpAsyncClient c(io_service_tcp, "192.168.1.200", "/onvif/device_service", docGetURIs.toString().toStdString());
        io_service_tcp.run();
        io_service_tcp.stop();

        std::cout << "Found an URI: " << c.getURI() << std::endl;

    } else{
        boost::asio::io_service io_service;
        QDomDocument docDiscover = xmlHelper->loadXml("xml/discover.xml");

        UdpSender s(io_service, boost::asio::ip::address::from_string("239.255.255.250"), docDiscover.toString().toStdString());
        io_service.run();
        io_service.stop();
    }

    delete xmlHelper;
}
