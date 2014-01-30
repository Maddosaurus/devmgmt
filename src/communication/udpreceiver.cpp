// TAKEN FROM: http://www.boost.org/doc/libs/1_37_0/doc/html/boost_asio/example/multicast/receiver.cpp
//
// receiver.cpp
// ~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "udpreceiver.h"

UdpReceiver::UdpReceiver(boost::asio::io_service& io_service, const boost::asio::ip::address& listen_address, const boost::asio::ip::address& multicast_address) : socket_(io_service)
{
    this->multicast_port = 3702;

  // Create the socket so that multiple may be bound to the same address.
    boost::asio::ip::udp::endpoint listen_endpoint(listen_address.to_v4(), multicast_port);
    socket_.open(listen_endpoint.protocol());
    socket_.set_option(boost::asio::ip::udp::socket::reuse_address(true));
    socket_.bind(listen_endpoint);

    // Join the multicast group.
    //socket_.set_option(boost::asio::ip::multicast::join_group(multicast_address));
    socket_.set_option(boost::asio::ip::multicast::join_group(multicast_address.to_v4(), listen_address.to_v4()));

    //set stream to zero
    oss.str("");
    socket_.async_receive_from(boost::asio::buffer(data_, max_length), sender_endpoint_, boost::bind(&UdpReceiver::handle_receive_from, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void UdpReceiver::handle_receive_from(const boost::system::error_code& error, size_t bytes_recvd)
{
  if (!error)
  {
      oss << data_;
      std::string ergebnis="";

    //Gesucht ist der Bereich zwischen <tt:Uri> und </tt:Uri>.
    //Das Ganze nun um 8 nach rechts verschoben, um den XML-Tag nicht mit in der Ausgabe zu haben
    std::size_t found = oss.str().find("<d:XAddrs>");
      if (found!=std::string::npos){
          std::size_t foundEnd = oss.str().find("</d:XAddrs>");
            if (found!=std::string::npos){
                ergebnis = oss.str().substr(found+10, foundEnd-found-10);
                //std::cout << ergebnis << std::endl;
                this->foundDevice = ergebnis;
                return;
            }
            else{
                std::cout << "No end found!!\n";
            }
      }

    socket_.async_receive_from( boost::asio::buffer(data_, max_length), sender_endpoint_, boost::bind(&UdpReceiver::handle_receive_from, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
  }
}

std::string UdpReceiver::getFoundDevice(){
    return this->foundDevice;
}
