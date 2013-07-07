#include "authenticator.h"
#include <iostream>
#include <fstream>

/*
 * Should look like this:
 *
 * Nonce – LKqI6G/AikKCQrN0zqZFlg==
 * Date – 2010-09-16T07:50:45Z
 * Password – userpassword
 * Resulting Digest – tuOSpGlFlIXsozq4HFNeeGeFLEI=
 *
 * wsse:Password is Base64( SHA-1 (nonce + created + password) ) <<--Official
 * B64ENCODE( SHA1( B64DECODE( Nonce ) + Date + Password ) )     <<--ONVIF doc
 */


#include <bitset>
#include <QString>
#include <QCryptographicHash>
#include <QObject>
#include <QDateTime>
#include <QUuid>

Authenticator::Authenticator()
{
}

void Authenticator::genToken(std::string user, std::string password, std::string result[]){

    QDateTime dt = QDateTime::currentDateTimeUtc();
    std::string time(dt.toString("yyyy-MM-ddThh:mm:ssZ").toStdString());

    QByteArray usrData[3];

    QByteArray nonce = QUuid::createUuid().toByteArray();
    QByteArray nonce_base64 = nonce.toBase64();



    usrData[0] = nonce;
    usrData[1] = QByteArray(time.c_str());
    usrData[2] = QByteArray(password.c_str());



    QCryptographicHash hash(QCryptographicHash::Sha1);
    hash.addData(nonce, nonce.length());
    hash.addData(usrData[1], usrData[1].length());
    hash.addData(usrData[2], usrData[2].length());

    QByteArray finish= hash.result();

    finish = finish.toBase64();


    result[0]=user;
    result[1]=finish.data();
    result[2]=nonce_base64.data();
    result[3]=time;

}

