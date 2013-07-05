#ifndef APP_H
#define APP_H

#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>



class App
{


public:
    App();
    std::string uuidGenerate();
    //enum TYPES { NVT = "dn:NetworkVideoTransmitter" };
    std::string buildProbeMessage(std::string probeMessageID, std::string types, std::string scopes);
};

#endif // APP_H
