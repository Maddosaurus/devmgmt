#include "app.h"


App::App()
{
}

std::string App::uuidGenerate() {
    boost::uuids::basic_random_generator<boost::mt19937> gen;
    boost::uuids::uuid uuid = gen();

    std::string sUuid = boost::lexical_cast<std::string>(uuid);
    return sUuid;

//    return boost::lexical_cast<std::string>(boost::uuids::random_generator());
}

std::string App::buildProbeMessage(std::string probeMessageID, std::string types, std::string scopes) {

}
