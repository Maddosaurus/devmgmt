#ifndef APP_H
#define APP_H

#include <string>

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "onv.h"

class App
{


public:
    App();
    std::string uuidGenerate();
    std::string buildProbeMessage(std::string probeMessageID, std::string types, std::string scopes);
    std::string sendMulticast(std::string castAddr, int port, std::string message);
    ONVIF::probematch readProbeMatches(std::string net_handle, std::string header);
};

#endif // APP_H
