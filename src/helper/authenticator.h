#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H

#include <string>
#include <sstream>


class Authenticator
{

public:
    Authenticator();
    void genToken(std::string user, std::string password, std::string result[]);

};

#endif // AUTHENTICATOR_H
