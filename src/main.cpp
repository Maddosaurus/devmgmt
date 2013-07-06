// This file generated by staff_codegen
// For more information please visit: http://code.google.com/p/staff/
// Client skeleton

#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <string>


#include <boost/array.hpp>
#include <boost/asio.hpp>

#include "app.h"
#include "device/getsystemdateandtime.h"
#include "device/envelope.h"
#include "onv.h"
#include "tcpasyncclient.h"
#include "udpsender.h"
#include "udpreceiver.h"
#include "helper/xmlhelper.h"

// the following macro eliminates the attributes
//BOOST_CLASS_IMPLEMENTATION(GetSystemDateAndTime, object_serializable)

int main(int argc, char* argv[])
{
    XmlHelper *xmlHelper = new XmlHelper;
    QDomDocument docDiscover = xmlHelper->loadXml("xml/discover.xml");
    QDomDocument docGetSystemDateAndTime = xmlHelper->loadXml("xml/device.GetSystemDateAndTime.xml");
    delete xmlHelper;



    try {
        boost::asio::io_service io_service;
        UdpSender s(io_service, boost::asio::ip::address::from_string("239.255.255.250"), docDiscover.toString().toStdString());
        io_service.run();
        //io_service.stop();

        TcpAsyncClient c(io_service, "192.168.1.200", "/onvif/device_service", docGetSystemDateAndTime.toString().toStdString());
        io_service.run();
        //io_service.stop();


//        std::ofstream ofs("filename.xml");
//        boost::archive::xml_oarchive oa(ofs);

//        std::ostringstream oss;

//        // the flag no_header eliminates the heading lines
//        unsigned int flags = boost::archive::no_header;

//        boost::archive::xml_oarchive oa(oss, flags);

//        SOAPENV::Envelope *envelope = new SOAPENV::Envelope();
//        oa << BOOST_SERIALIZATION_NVP(envelope);



//        //GetSystemDateAndTime *gsdt = new GetSystemDateAndTime(1, 2, 3.0);
//        //oa << BOOST_SERIALIZATION_NVP(gsdt);

//        //std::cout << oss.str() << std::endl;

//        //delete gsdt;
//        delete envelope;

    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << "\n";
    }
}


/*

int main(int argc, char* argv[])
{

    // Send WS-Discovery Probe, collect the responses and then
    // process the responses.
        //probematch_type probematcheslist[]={};
    std::list<ONVIF::probematch> probematcheslist;

    // Send probe. See chapter 4.3.1 for details
    ONVIF::probe probe = ONVIF::DiscoverySendProbe("dn:NetworkVideoTransmitter", "onvif://www.onvif.org");

    // Wait a while for responses
    //while (data_available_and_not_timeout(probe.net_handle))
    for(int i=0; i<500; i++) //Quick 'n Dirty
    {
        // This fetch next probe match so that we can put it into the list
        // See chapter 4.3.2 for details
        ONVIF::probematch probematch = ONVIF::DiscoveryReadResponse(probe);

        // Store info about the match, first check for duplicates
//        if (!in_list(probematcheslist, probematch))
//        {
//            add_to_list(probematcheslist, probematch);
//        }

        //Spare much work: Use a Map.
        bool inList=false;
        for (std::list<ONVIF::probematch>::const_iterator iterator = probematcheslist.begin(), end = probematcheslist.end(); iterator != end; iterator++) {
            if(probematch.endpointAddress.compare(iterator->endpointAddress)){
                inList=true;
                break;
            }
        }
        if(!inList)
            probematcheslist.push_back(probematch);
    }

    // Process the responses, see chapter 5.1.3 for details.
    for (std::list<ONVIF::probematch>::const_iterator iterator = probematcheslist.begin(), end = probematcheslist.end(); iterator != end; iterator++)
    {
        ONVIF::ProcessMatch(*iterator);
    }

  return 0;
}
*/

