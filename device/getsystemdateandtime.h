#ifndef GETSYSTEMDATEANDTIME_H
#define GETSYSTEMDATEANDTIME_H

//#include <fstream>
#include <list>
#include <string>

#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

// http://stackoverflow.com/questions/3457467/serialize-to-xml-using-boostserialization

class GetSystemDateAndTime
{
private:
//    std::string m_bread, m_cheese;
//    std::list<std::string> m_meats;
//    bool m_spicy_eggplant_p;

//    friend class boost::serialization::access;
//    template<class archive>
//    void serialize(archive& ar, const unsigned int version)
//    {
//        using boost::serialization::make_nvp;
//        ar & make_nvp("Bread", m_bread);
//        ar & make_nvp("Cheese", m_cheese);
//        ar & make_nvp("Meats", m_meats);
//        ar & make_nvp("Add Spicy Eggplant", m_spicy_eggplant_p);
//    }

    int a;
    int b;
    float c;



    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar,
            const unsigned int version) {
        using boost::serialization::make_nvp;
        ar & make_nvp("bcd", a);
        ar & BOOST_SERIALIZATION_NVP(b);
        ar & BOOST_SERIALIZATION_NVP(c);

    }
public:

    inline GetSystemDateAndTime(int a, int b, float c) {
        this->a = a;
        this->b = b;
        this->c = c;
    }
};

#endif // GETSYSTEMDATEANDTIME_H
