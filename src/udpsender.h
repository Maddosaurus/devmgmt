#ifndef UDPSENDER_H
#define UDPSENDER_H

#include <iostream>
#include <sstream>
#include <string>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

//const short multicast_port = 30001;
const short multicast_port = 3702;
const int max_message_count = 10;


class UdpSender{

private:
    boost::asio::ip::udp::endpoint endpoint_;
    boost::asio::ip::udp::socket socket_;
    boost::asio::deadline_timer timer_;
    int message_count_;
    std::string message_;

public:
    UdpSender();
    UdpSender(boost::asio::io_service& io_service, const boost::asio::ip::address& multicast_address, const std::string &message);

    void handle_send_to(const boost::system::error_code& error);
    void handle_timeout(const boost::system::error_code& error);
};

#endif // UDPSENDER_H
