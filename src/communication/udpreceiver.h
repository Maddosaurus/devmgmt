#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <boost/asio.hpp>
#include "boost/bind.hpp"

class UdpReceiver
{
private:
    std::ostringstream oss;
    std::string foundDevice;

    short multicast_port;
    enum { max_length = 2048 };
    char data_[max_length];

    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint sender_endpoint_;

public:
    UdpReceiver();
    UdpReceiver(boost::asio::io_service& io_service, const boost::asio::ip::address& listen_address,const boost::asio::ip::address& multicast_address);
    void handle_receive_from(const boost::system::error_code& error, size_t bytes_recvd);
    std::string getFoundDevice();
};

#endif // UDPRECEIVER_H
