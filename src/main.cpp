// This file generated by staff_codegen
// For more information please visit: http://code.google.com/p/staff/
// Client skeleton

#include <memory>
#include <rise/common/Log.h>
#include <staff/common/Exception.h>
#include <staff/client/ServiceFactory.h>
#include "devicemgmt.h"
#include "onvif.h"
#include "xmlmime.h"
#include ".h"
#include "b.h"
#include "ws_addr.h"
#include "bf.h"
#include "xml.h"
#include "t.h"
#include "include.h"
#include <boost/asio.hpp>

#include <iostream>
#include <boost/array.hpp>

#include "app.h"


//
// receiver.cpp
// ~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <string>

#include "udpreceiver.h"
#include "onv.h"




int main(int argc, char* argv[])
{
//  try
//  {
//    if (argc != 3)
//    {
//      std::cerr << "Usage: receiver <listen_address> <multicast_address>\n";
//      std::cerr << "  For IPv4, try:\n";
//      std::cerr << "    receiver 0.0.0.0 239.255.0.1\n";
//      std::cerr << "  For IPv6, try:\n";
//      std::cerr << "    receiver 0::0 ff31::8000:1234\n";
//      return 1;
//    }

//    boost::asio::io_service io_service;
//    UdpReceiver r(io_service,
//        boost::asio::ip::address::from_string(argv[1]),
//        boost::asio::ip::address::from_string(argv[2]));
//    io_service.run();
//  }
//  catch (std::exception& e)
//  {
//    std::cerr << "Exception: " << e.what() << "\n";
//  }

    // Send WS-Discovery Probe, collect the responses and then
    // process the responses.
    probematch_type probematcheslist[]={};

    // Send probe. See chapter 4.3.1 for details
    ONVIF::probe probe = ONVIF::DiscoverySendProbe(scopes, types);

    // Wait a while for responses
    while (data_available_and_not_timeout(probe.net_handle))
    {
        // This fetch next probe match so that we can put it into the list
        // See chapter 4.3.2 for details
        ONVIF::probe probematch = ONVIF::DiscoveryReadResponse(probe);

        // Store info about the match, first check for duplicates
        if (!in_list(probematcheslist, probematch))
        {
            add_to_list(probematcheslist, probematch);
        }
    }

    // Process the responses, see chapter 5.1.3 for details.
    for(int i=0; i < probematcheslist.length; i++)
    {
        ONVIF::ProcessMatch(probeMatch);
    }

  return 0;
}

data_available_and_not_timeout()
