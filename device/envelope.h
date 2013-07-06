#ifndef ENVELOPE_H
#define ENVELOPE_H

#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include "device/body.h"

namespace SOAPENV {

    class Envelope
    {
    private:
        SOAPENV::Body body;

        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar,
                const unsigned int version) {
            using boost::serialization::make_nvp;
            ar & BOOST_SERIALIZATION_NVP(body);
        }

    public:
        Envelope();
    };

}

#endif // ENVELOPE_H
