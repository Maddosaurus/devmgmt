#ifndef BODY_H
#define BODY_H

#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

namespace SOAPENV {

    class Body
    {
    private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar,
                const unsigned int version) {
            using boost::serialization::make_nvp;
            //ar & BOOST_SERIALIZATION_NVP(body);
        }

    public:
        Body();
    };

}

#endif // BODY_H
