#ifndef XMLHELPER_H
#define XMLHELPER_H

#include <iostream>

#include <QtXmlPatterns>
#include <QtXml/QDomDocument>

class XmlHelper
{
public:
    XmlHelper();
    QDomDocument loadXml(std::string filename);
};

#endif // XMLHELPER_H
