#include "xmlhelper.h"

XmlHelper::XmlHelper() {

}

QDomDocument XmlHelper::loadXml(std::string filename)
{
    QDomDocument doc;
    QFile file(QString::fromStdString(filename));

    if (!file.open(QIODevice::ReadOnly)) {
        // TODO: Failure handling
        return doc;
    }

    if (!doc.setContent(&file)) {
        file.close();
        // TODO: Failure handling
        return doc;
    }

    std::cout << doc.toString().toStdString() << std::endl;

    file.close();

    return doc;
}
