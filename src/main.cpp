#include <iostream>
#include <algorithm>

#include <boost/array.hpp>
#include <boost/asio.hpp>

#include "src/communication/tcpasyncclient.h"
#include "src/communication/udpsender.h"
#include "src/communication/udpreceiver.h"
#include "helper/xmlhelper.h"
#include "helper/authenticator.h"

void usage(char const* progName) {
    std::cout << "Usage: " << progName << " -r/-s -u <username> <password>\n";
    std::cout << "\t -r for receiving info \n";
    std::cout << "\t -s for sending a discovery.\n";
    std::cout << "\t username and password are not needed for -s, but required by -r.\n";
    std::cout << "\t Usually, you want to have one receiver and one sender.\n";
}

int main(int argc, char** argv)
{
    char const* progName = argv[0];

    bool isReceiver = false;
    bool sUsed = false;
    bool rUsed = false;
    std::string user = "";
    std::string pass = "";

    if(argc < 2 || argc > 6){
        usage(argv[0]);
        return 1;
    }
    while(argc > 1) {
        char* const opt = argv[1];
        if(opt[0] != '-')
            break;

        switch(opt[1]){
        case 's': {
            isReceiver = false;
            sUsed = true;
            break;
        }
        case 'r': {
            isReceiver = true;
            rUsed = true;
            break;
        }
        case 'u': {             // specify a username and password
            if (argc < 4)       // there's no argv[3] (for the "password")
                usage(progName);
            user = argv[2];
            pass = argv[3];
            argv += 2; argc -= 2;
            break;
        }
        default: {
            usage(progName);
            return 1;
            break;
        }
        }
        ++argv; --argc;
    }

    //Just some additional checking.
    if(sUsed && rUsed){                 // Never ever use r and s at the same time!
        std::cout << "Cannot use -r and -s at the same time. Aborting!" << std::endl;
        usage(progName);
        return 1;
    } else if( (rUsed && (user == "") ) || (rUsed && (pass == "")) ){       // Make sure user provides credentials, if using -r
        std::cout << "Sorry, you need to specify username and password for the -r backend. Aborting!" << std::endl;
        usage(progName);
        return 1;
    }



     XmlHelper *xmlHelper = new XmlHelper;


    //The receiver waits for a WS-Discovery-Multicast and then queries the Stream-URI
    if(isReceiver){
        boost::asio::io_service io_service_udpr;
        boost::asio::io_service io_service_tcp;

        //Generate the digest for authentication purposes
        Authenticator *auth = new Authenticator();
        std::string token[4];
        auth->genToken(user,pass,token);
        delete auth;

        //Wait for the Multicast
        UdpReceiver r(io_service_udpr, boost::asio::ip::address::from_string("0.0.0.0"), boost::asio::ip::address::from_string("239.255.255.250"));
        io_service_udpr.run();
        io_service_udpr.stop();
        std::cout << "Found a Device: " << r.getFoundDevice() << std::endl;
        std::string text = r.getFoundDevice();

        //parse the returned url. Format: http://<ipaddress>/some/link
        std::string base_ip="";
        std::string query="";

        if(text != ""){
            size_t sp = text.find_first_of('/', 7); // 7 -> don't match http://, instead skip it
            if(sp != std::string::npos){
                base_ip = std::string(text.begin()+7, text.begin()+sp);
                sp = text.find_first_of('/', 7);
                if(sp != std::string::npos){
                    query = std::string(text.begin()+sp, text.end());
                }
            }
            std::cout << "Found base ip: " << base_ip << std::endl << "and url: " << query << std::endl;
        }

        //Now query camera for the stream
        QDomDocument docGetURIs = xmlHelper->loadXml("xml/device.GetStreamURI.xml");
        QDomDocument docAuthHeader = xmlHelper->loadXml("xml/auth.xml");


        //build the XML for the request
        docGetURIs.elementsByTagName("soap:Envelope").at(0).appendChild((docAuthHeader.elementsByTagName("s:Header").at(0)));

        docGetURIs.elementsByTagName("Username").at(0).firstChild().setNodeValue(token[0].data());
        docGetURIs.elementsByTagName("Password").at(0).firstChild().setNodeValue(token[1].data());
        docGetURIs.elementsByTagName("Nonce").at(0).firstChild().setNodeValue(token[2].data());
        docGetURIs.elementsByTagName("Created").at(0).firstChild().setNodeValue(token[3].data());

        if(base_ip != "" && query != ""){
            TcpAsyncClient c(io_service_tcp, base_ip, query, docGetURIs.toString().toStdString());
            io_service_tcp.run();
            io_service_tcp.stop();

            if(c.getURI() != "")
                std::cout << "Found an URI: " << c.getURI() << std::endl;
        }

    } else{
        boost::asio::io_service io_service;
        QDomDocument docDiscover = xmlHelper->loadXml("xml/discover.xml");

        UdpSender s(io_service, boost::asio::ip::address::from_string("239.255.255.250"), docDiscover.toString().toStdString());
        io_service.run();
        io_service.stop();
    }

    delete xmlHelper;
}
